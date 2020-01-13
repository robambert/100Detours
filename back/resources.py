# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 16:35:08 2019

@author: simed
"""


from flask_restful import Resource, reqparse
from flask_jwt_extended import (create_access_token, create_refresh_token, jwt_required, jwt_refresh_token_required, get_jwt_identity, get_raw_jwt)
from main import db_planning, db_user, db_revoked_tokens
loginparser = reqparse.RequestParser()
loginparser.add_argument('username', help = 'This field cannot be blank', required = True)
loginparser.add_argument('password', help = 'This field cannot be blank', required = True)

from models import RevokedTokenModel,UserModel

class UserPlanning(Resource):
    @jwt_required
    def get(self):
        user=get_jwt_identity()
        #planning=planning_db.get_user_planning(user)
        #html_page=get_html_page(user, planning) # FONCTION a ecrire, fais le lien avec le front.
        #return render_template(html_page)


class UserRegistration(Resource):
    def post(self):
        data = loginparser.parse_args()
        
        if db_user.find_by_username(data['username']):
            return {'message': 'User {} already exists'.format(data['username'])}
        new_user = {'username' : data['username'], 'password' : UserModel.generate_hash(data['password'])}

        try:
            db_user.insert(new_user)
            return {
                'message': 'User {} was created'.format(data['username'])
                }
        except:
            return {'message': 'Something went wrong'}, 500
    
        
class UserLogin(Resource):
    def post(self):
        data = loginparser.parse_args()
        current_user= db_user.find_by_username(data['username'])
        if not current_user:
            return {'message': 'User {} doesn\'t exist'.format(data['username'])}
        if UserModel.verify_hash(data['password'], current_user['password']):
            access_token = create_access_token(identity = data['username'])
            refresh_token = create_refresh_token(identity = data['username'])
            return {
                'message': 'Logged in as {}'.format(current_user['username']),
                'access_token': access_token,
                'refresh_token': refresh_token
                }
        else:
            return {'message': 'Wrong credentials'}
      
      
class UserLogoutAccess(Resource):
    @jwt_required
    def post(self):
        jti = get_raw_jwt()['jti']
        try:
            db_revoked_tokens
            return {'message': 'Access token has been revoked'}
        except:
            return {'message': 'Something went wrong'}, 500


class UserLogoutRefresh(Resource):
    @jwt_refresh_token_required
    def post(self):
        jti = get_raw_jwt()['jti']
        try:
            db_revoked_tokens.insert({'token' : jti})
            return {'message': 'Refresh token has been revoked'}
        except:
            return {'message': 'Something went wrong'}, 500
      
      
class TokenRefresh(Resource):
    @jwt_refresh_token_required
    def post(self):
        current_user = get_jwt_identity()
        access_token = create_access_token(identity = current_user)
        return {'access_token': access_token}
      
      
"""     
class InfirmierAdder(Resource):
    """
    #Idem au login, mais se fais ici une fois connecté, pour ajouter de nouveaux infirmiers(usertype = 1)
    
    #il faut surement créer une nouvelle table infirmiers, pour placer les données perso de l'infirmiers crée
    #actuellement, seule son nom de compte/mot de passe ( provisoire, choisi par le manager ou généré aléatoirement) sont exigés.'
    """
    @jwt_required
    def post(self):
        username = get_jwt_identity()
        current_user = db_user.find({'username' : username})[0]
#        if current_user.usertype == 1:
#            return {'message' : 'Acces denied'}, 500
        data=loginparser.parse_args()
        new_user = {'username' : data['username'], 'password' : MongoUserModel.generate_hash(data['password'])}
        try:
            db_user.insert_one(new_user)
            return {
                'message': 'User {} was created'.format(data['username'])
                }, 200
        except:
            return {'message': 'Something went wrong'}, 500
    def get(self):
        username = get_jwt_identity()
        current_user = db_user.find({'username' : username})[0]
        if current_user.usertype == 1:
            return {'message' : 'Acces denied'}, 500
        #html_page=get_html_page()# ENcore une fois fonction a coder, lien avec le front
        #return render_template(html_page)
"""     