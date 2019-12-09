# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 16:34:10 2019

@author: simed
"""

from main import app
from flask import jsonify
@app.route('/')
def index():
    return jsonify({'message': 'OK BORIS!'})