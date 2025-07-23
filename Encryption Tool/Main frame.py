from tkinter import *
from tkinter import filedialog
from PIL import ImageTk, Image
import os

def open_file():
    os.system('python "C:\\Users\\MANOJ\\Desktop\\Encryption Tool\\Gui.py"')

def open_file1():
    os.system('python "C:\\Users\\MANOJ\\Desktop\\Encryption Tool\\File.py"')

def open_file2():
    os.system('python "C:\\Users\\MANOJ\\Desktop\\Encryption Tool\\Audio.py"')

def open_file3():
    os.system('python "C:\\Users\\MANOJ\\Desktop\\Encryption Tool\\Encrypt.py"')

t=Tk()
t.geometry("520x400")
t.title("Encryption Tool")
img=Image.open('C:\\Users\\MANOJ\\Downloads\\extra.jpeg')
bg=ImageTk.PhotoImage(img)
label1=Label(t,image=bg)
label1.place(x=0,y=0)
t.configure(bg="grey")
Label(t,text="ENCRYPTION TOOL",font="impack 18 bold",bg="navy blue",fg="white").place(x=140,y=30)







def audio():
    f2=Frame()
    f2.place(x=0,y=0,width=520,height=500)
    
    f2.configure(bg="blue")
    
    Label(t,text="AUDIO ENCRYPTION",font="impack 18 bold",bg="navy blue",fg="white").place(x=150,y=30)

    b5=Button(t,text="ENCRYPT",font="arial 15 bold",bg="light blue",command=open_file3)
    b5.place(x=80,y=200)
    b6=Button(t,text="DECRYPT",font="arial 15 bold",bg="light blue",command=open_file2)
    b6.place(x=300,y=200)
    input()
    print("Image Decrypted")


b1=Button(t,text="Encrypt Image",font="arial 15 bold",bg="blue",command=open_file1)
b1.place(x=20,y=200)
b2=Button(t,text="Encrypt Text",font="arial 15 bold",bg="blue",command=open_file)
b2.place(x=360,y=200)
b3=Button(t,text="Encrypt Audio",font="arial 15 bold",bg="blue",command=audio)
b3.place(x=190,y=200)
t.mainloop()
    
