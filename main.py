from flask import Flask, render_template, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def get_mode():
    conn = sqlite3.connect("vehicle.db")
    cur = conn.execute("SELECT mode FROM newVsignal WHERE id=1")
    row = cur.fetchone()
    conn.close()
    if row:
        return row[0]
    return "None"

@app.route('/')
def home():
    mode = get_mode()
    return render_template("index.html", msg=mode)

# ✅ Route with dynamic direction in URL
@app.route('/<mode>')
def mode_page(mode):
    return render_template("index.html", msg=mode)

@app.route('/set_mode', methods=['POST'])
def set_mode():
    mode = request.form.get("mode")

    # ✅ Store in database
    con = sqlite3.connect("vehicle.db")
    cur = con.execute("SELECT * FROM newVsignal WHERE id=1")
    row = cur.fetchone()

    if row is None:
        con.execute("INSERT INTO newVsignal (id, mode) VALUES (?, ?)", (1, mode))
    else:
        con.execute("UPDATE newVsignal SET mode=? WHERE id=1", (mode,))
    con.commit()
    con.close()

    # ✅ Redirect the user to URL showing the mode
    return redirect(url_for('mode_page', mode=mode))

@app.route('/mode_status')
def mode_status():
    return get_mode()

if __name__ == '__main__':
    app.run(host='0.0.0.0')
