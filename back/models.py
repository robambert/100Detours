# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 16:35:01 2019

@author: simed
"""

from passlib.hash import pbkdf2_sha256 as sha256


class MongodbManager:
    def __init__(self, database):
        self.db=database
        
    def find_by_id(self, id_):
        return list(self.db.find({'_id' : id_}))
    
    def insert(self, content):
        self.db.insert_one(content)

class PlanningModel(MongodbManager):
    def __init__(self, database):
        super.__init__(self, database)
        
    def find_by_username(self, username):
        result=list(self.db.find({"username" : username}))
        if len(result) == 0:
            return None
        return result[0]
    


class UserModel(MongodbManager):
    
    def __init__(self, database):
        super.__init__(self, database)
        
    @staticmethod
    def generate_hash(password):
        return sha256.hash(password)
    
    @staticmethod
    def verify_hash(password, hash):
        return sha256.verify(password, hash)

        
    @classmethod
    def find_by_username(self, username):
        result=list(self.db.find({"username" : username}))
        if len(result) == 0:
            return None
        return result[0]
    
        
class NursesModel:
    def __init__(self, database):
        super.__init__(self, database)
        

        
class PatientModel:
    def __init__(self, database):
        super.__init__(self, database)
        

        
class RevokedTokenModel(MongodbManager):
    def __init__(self, database):
        super.__init__(self, database)
    
    def is_jti_blacklisted(self, jti):
        number = self.db.find({'token' : jti}).count()
        
        return True if number !=0 else False
    

