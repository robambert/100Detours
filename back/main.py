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
app.config['SECRET_KEY'] = 'GYUOgygb87G8B264NHYUnju'
app.config['JWT_SECRET_KEY'] = 'EBJOHD065EHE7ELEO'
app.config['JWT_BLACKLIST_ENABLED'] = True
app.config['JWT_BLACKLIST_TOKEN_CHECKS'] = ['access', 'refresh']
jwt = JWTManager(app)

db=pymongo.MongoClient('mongodb://localhost:27017')["mongo"]
db_planning=db.planning
db_user=db.users
if db_user.count() ==0:
    db_user.insert_one({'username' : 'admin', 'password' : '$pbkdf2-sha256$29000$vldKKQXAmDOG0Pq/l5JSCg$kCw9QC8i5.rutQNl6dFTTFhLEx3cC/sjO6XhCYDaUMQ'})

db_revoked_tokens=db.tokens


import views, models
import resources
@jwt.token_in_blacklist_loader
def check_if_token_in_blacklist(decrypted_token):
    jti = decrypted_token['jti']
    return models.RevokedTokenModel(db_revoked_tokens).is_jti_blacklisted(jti)


api.add_resource(resources.UserRegistration, '/registration')
api.add_resource(resources.UserLogin, '/login')
api.add_resource(resources.UserLogoutAccess, '/logout/access')
api.add_resource(resources.UserLogoutRefresh, '/logout/refresh')
api.add_resource(resources.TokenRefresh, '/token/refresh')
api.add_resource(resources.AllUsers, '/users')
api.add_resource(resources.UserPlanning, '/planning')
api.add_resource(resources.InfirmierAdder, '/manage/add')# page pour ajouter des infirmiers


app.run(debug=True)



