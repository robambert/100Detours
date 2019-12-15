# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 16:35:01 2019

@author: simed
"""

from main import db
from passlib.hash import pbkdf2_sha256 as sha256


class PlanningModel:
    def __init__(self, database):
        self.db=database
        
    def insert(self, planning):
        self.db.insert_one(planning)
        
    def get_user_planning(self, user_id):
        return list(self.db.find({"_id" : user_id}))
    


class UserModel(db.Model):
    __tablename__ = 'users'

    id = db.Column(db.Integer, primary_key = True)
    username = db.Column(db.String(120), unique = True, nullable = False)
    password = db.Column(db.String(120), nullable = False)
    usertype = db.Column(db.Integer, default=1) # 0 pour l'admin, 1 pour les infirmiers
    
    @classmethod
    def return_all(cls):
        def to_json(x):
            return {
                'username': x.username,
                'password': x.password
            }
        return {'users': list(map(lambda x: to_json(x), UserModel.query.all()))}
    
    @staticmethod
    def generate_hash(password):
        return sha256.hash(password)
    
    @staticmethod
    def verify_hash(password, hash):
        return sha256.verify(password, hash)

    @classmethod
    def delete_all(cls):
        try:
            num_rows_deleted = db.session.query(cls).delete()
            db.session.commit()
            return {'message': '{} row(s) deleted'.format(num_rows_deleted)}
        except:
            return {'message': 'Something went wrong'}
        
    @classmethod
    def find_by_username(cls, username):
       return cls.query.filter_by(username = username).first()
    
    
    def save_to_db(self):
        db.session.add(self)
        db.session.commit()
        
class RevokedTokenModel(db.Model):
    __tablename__ = 'revoked_tokens'
    id = db.Column(db.Integer, primary_key = True)
    jti = db.Column(db.String(120))
    
    def add(self):
        db.session.add(self)
        db.session.commit()
    
    @classmethod
    def is_jti_blacklisted(cls, jti):
        query = cls.query.filter_by(jti = jti).first()
        return bool(query)
    

