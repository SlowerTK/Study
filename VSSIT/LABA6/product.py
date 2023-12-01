from flask import Flask, request, jsonify
from flask_cors import CORS
import os

app = Flask(__name__)
CORS(app)

@app.route('/submit', methods=['POST'])
def submit():
    data = request.get_json()
    for product in data:
        print(f"ID: {product['id']}, Count: {product['count']}")

    F = open('DataBase.txt', 'r')
    lines = F.readlines()
    F.close()
    F = open('DataBase.ntxt', 'w')
    for product in data:
        for i in range(len(lines)):
            if lines[i] == f"id: {product['id']}\n":
                count = int(lines[i+1][7:])
                if int(product['count']) > count:
                    F.close()
                    return jsonify({'status': 'error', 'message': 'Вы запросили больше чем есть на складе'}), 400
                count -= int(product['count'])
                lines[i+1] = f"count: {count}\n"
                break
    F.writelines(lines)
    F.close()
    
    os.remove('DataBase.txt')
    os.rename('DataBase.ntxt', 'DataBase.txt')

    return jsonify({'status': 'success'}), 200

@app.route('/get_count', methods=['GET'])
def get_count():
    product_id = request.args.get('id')
    F = open('DataBase.txt', 'r')
    for line in F:
        if line == f"id: {product_id}\n":
            break
    count = F.readline()
    count = count[7:]
    F.close()
    return jsonify({'count': count}), 200

if __name__ == '__main__':
    app.run()