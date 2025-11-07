import sqlite3
con=sqlite3.connect("vehicle.db")
con.execute("CREATE TABLE newVsignal(id INTEGER PRIMARY KEY AUTOINCREMENT, mode TEXT)")