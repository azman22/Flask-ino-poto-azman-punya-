from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
    if request.is_json:
        data = request.get_json()
        co2 = data.get('CO2')
        
        # Validate CO2 data (ensure it is not None)
        if co2 is not None:
            response_message = {
                'status': 'success',
                'data_received': {
                    'CO2': co2
                }
            }
            
            print(f"Received CO2 data: {co2}")
            
            return jsonify(response_message), 200
        else:
            response_message = {
                'status': 'error',
                'message': 'Invalid data'
            }
            return jsonify(response_message), 400
    else:
        response_message = {
            'status': 'error',
            'message': 'Request must be JSON'
        }
        return jsonify(response_message), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
