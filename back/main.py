# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 14:55:35 2019

@author: simed
"""

from flask import Flask
from flask_restful import Api
from flask_sqlalchemy import SQLAlchemy
from flask_jwt_extended import JWTManager
import pymongo

app = Flask(__name__)
api = Api(app)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///app.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'GYUOgygb87G8B264NHYUnju'
db = SQLAlchemy(app)
app.config['JWT_SECRET_KEY'] = 'EBJOHD065EHE7ELEO'
app.config['JWT_BLACKLIST_ENABLED'] = True
app.config['JWT_BLACKLIST_TOKEN_CHECKS'] = ['access', 'refresh']

jwt = JWTManager(app)
mongo_db=pymongo.MongoClient('mongodb://localhost:27017')["mongo"]
db_planning=mongo_db['planning']
user_db=mongo_db['users']

import views, models
planning_db=models.PlanningModel(db_planning)

import resources
@jwt.token_in_blacklist_loader
def check_if_token_in_blacklist(decrypted_token):
    jti = decrypted_token['jti']
    return models.RevokedTokenModel.is_jti_blacklisted(jti)


@app.before_first_request
def create_tables():
    db.create_all()

api.add_resource(resources.UserRegistration, '/registration')
api.add_resource(resources.UserLogin, '/login')
api.add_resource(resources.UserLogoutAccess, '/logout/access')
api.add_resource(resources.UserLogoutRefresh, '/logout/refresh')
api.add_resource(resources.TokenRefresh, '/token/refresh')
api.add_resource(resources.AllUsers, '/users')
api.add_resource(resources.SecretResource, '/secret')

app.run(debug=True)



