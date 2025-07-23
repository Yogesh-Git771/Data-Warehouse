from tkinter import *
from tkinter import messagebox
import base64
from PIL import ImageTk,Image

screen=Tk()
screen.geometry("500x500")
screen.title("ENCRYPTION TOOL")
img=Image.open('C:\\Users\\MANOJ\\Downloads\\image.jpeg')
bg=ImageTk.PhotoImage(img)
label1=Label(screen,image=bg)
label1.place(x=0,y=0)

def encrypt():
    password=code.get()
    if password=="1234":
        screen1=Toplevel(screen)
        screen1.title("ENCRYPTION")
        screen1.geometry("400x250")
        screen1.configure(bg="green")
        message=text1.get(1.0,END)
        encode_message=message.encode("ascii")
        base64_bytes=base64.b64encode(encode_message)
        encrypt=base64_bytes.decode("ascii")


        Label(screen1,text="The message has been encrypted",font="impack 10 bold").place(x=90,y=6)
        text2= Text(screen1,font="30",bd=4,wrap=WORD)
        text2.place(x=2,y=30,width=390,height=180)
        text2.insert(END,encrypt)

    elif(password==""):
        messagebox.showerror("Error!!!!","Please enter the secret key")
    elif(password!="1234"):
        messagebox.showerror("Oopss!!!!","Invalid secret key")


def decrypt():
    password=code.get()
    if password=="1234":
        screen2=Toplevel(screen)
        screen2.title("DECRYPTION")
        screen2.geometry("400x250")
        screen2.configure(bg="red")
        message=text1.get(1.0,END)
        encode_message=message.encode("ascii")
        base64_bytes=base64.b64decode(encode_message)
        encrypt=base64_bytes.decode("ascii")

        Label(screen2,text="The message has been decrypted",font="impack 10 bold").place(x=90,y=6)
        text2= Text(screen2,font="30",bd=4,wrap=WORD)
        text2.place(x=2,y=30,width=390,height=180)
        text2.insert(END,encrypt)

    elif(password==""):
        messagebox.showerror("Error!!!!","Please enter the secret key")
    elif(password!="1234"):
        messagebox.showerror("Oopss!!!!","Invalid secret key")


def reset():
    text1.delete(1.0,END)
    code.set("")


Label(screen,text="ENTER MESSAGE FOR ENCRYPTION & DECRYPTION",font="impack 14 bold",bg="light green").place(x=5,y=6)
text1=Text(screen,bd=4,font="14")
text1.place(x=45,y=45,width=410,height=120)

Label(screen,text="ENTER SECRET KEY",font="impack 13 bold",bg="yellow").place(x=180,y=200)
code=StringVar()
Entry(textvariable=code,bd=6,font="30",show="*").place(x=155,y=240)
Button(screen,text="ENCRYPT",font="arial 15 bold",bg="white",fg="green",command=encrypt).place(x=50,y=300)
Button(screen,text="DECRYPT",font="arial 15 bold",bg="white",fg="red",command=decrypt).place(x=350,y=300)
Button(screen,text="RESET",font="arial 15 bold",bg="white",fg="blue",command=reset).place(x=200,y=350)

mainloop()



        
