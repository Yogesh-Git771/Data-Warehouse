from tkinter import *
from tkinter import filedialog
from PIL import ImageTk, Image
import os



root=Tk()
root.geometry("500x400")
root.title("Encryption and Decryption")
img=Image.open('C:\\Users\\MANOJ\\Downloads\\image.jpeg')
bg=ImageTk.PhotoImage(img)
label1=Label(root,image=bg)
label1.place(x=0,y=0)
root.configure(bg="grey")
Label(root,text="IMAGE ENCRYPTION",font="impack 18 bold",bg="yellow",fg="black").place(x=140,y=30)
Label(root,text="Enter Secret Key",font="impack 18 bold",bg="white",fg="blue").place(x=160,y=100)


def encrypt_image():
    file1=filedialog.askopenfile(mode='r',filetype=[('jpg file','*.jpg'),('png file','*.png')])
    if file1 is not None:
        #print(file1)

        file_name=file1.name
        key=entry1.get(1.0,END)
        print(file_name)
        print("Entered Key:",key)
        fi=open(file_name,'rb')
        image=fi.read()
        fi.close()
        image=bytearray(image)
        for index,values in enumerate(image):
            #image[index]=values^int(key)
             image[index] = (values ^ int(key)) % 256

        file=open(file_name,'wb')
        file.write(image)
        file.close()




def decrypt_image():
    file1=filedialog.askopenfile(mode='r',filetype=[('jpg file','.jpg'),('png file','.png')])
    if file1 is not None:
        file_name=file1.name
        key=entry1.get(1.0,END)
        print(file_name)
        print("Entered Key:",key)
        fi=open(file_name,'rb')
        image=fi.read()
        fi.close()
        image=bytearray(image)
        for index,values in enumerate(image):
            #image[index]=values^int(key)
            image[index] = (values ^ int(key)) % 256
        file=open(file_name,'wb')
        file.write(image)
        file.close()



      #print("Image Encrypted")
      #input()
       #print("Image Decrypted")

b1=Button(root,text="ENCRYPT",font="arial 15 bold",bg="light blue",fg="black",command=encrypt_image)
b1.place(x=190,y=300)
entry1=Text(root,height=2,width=20)
entry1.place(x=170,y=200)

root.mainloop()

