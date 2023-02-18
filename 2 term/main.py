from flask import Flask, render_template
import requests
import json

# Здесь находится сервер и больше ничего
def get_html_page(url):
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2228.0 Safari/537.36"
    }
    try:
        r = requests.get(url, headers=headers)
    except requests.exceptions.RequestException:
        html = None
    else:
        if r.ok:
            html = r.text
    return html


app = Flask(__name__)


@app.route("/")
def index_0():
    return render_template("index.html")


@app.route("/index", methods=["POST", "GET"])
def index():
    return render_template("index.html")


@app.route("/et", methods=["POST", "GET"])
def et():
    return render_template("et.html")


@app.route("/data", methods=["POST", "GET"])
def get_data():
    with open("aaaaaaaaaaa.txt", encoding="utf-8") as f:
        data = json.load(f)
    return json.dumps(data)


if __name__ == "__main__":
    app.run()
