# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 16:35:01 2019

@author: simed
"""

from passlib.hash import pbkdf2_sha256 as sha256


class PlanningModel:
    def __init__(self, database):
        self.db=database
        
    def insert(self, planning):
        self.db.insert_one(planning)
        
    def get_user_planning(self, user_id):
        return list(self.db.find({"_id" : user_id}))
    


class MongoUserModel:
    
    def __init__(self, database):
        self.db=database
        
    @staticmethod
    def generate_hash(password):
        return sha256.hash(password)
    
    @staticmethod
    def verify_hash(password, hash):
        return sha256.verify(password, hash)

        
    @classmethod
    def find_by_username(self, username):
       return list(self.db.find({'username' : username}))
    
    
    def insert(self, user):
        self.db.insert_one(user)
        

        
class RevokedTokenModel:
    
    def __init__(self, database):
        self.db = database
    
    def insert(self, token):
        self.db.insert_one(token)
    
    def is_jti_blacklisted(self, jti):
        number = self.db.find({'token' : jti}).count()
        
        return True if number !=0 else False
    

