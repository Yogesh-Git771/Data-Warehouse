from cryptography.fernet import Fernet

key=Fernet.generate_key()
print(key)

fernet=Fernet(key)
with open('key.key','wb') as filekey:
    filekey.write(key)


with open('key.key','rb') as filekey:
    key=filekey.read()


with open('sample-6s.mp3','rb') as file:
    originalaudio=file.read()


encrypted=fernet.encrypt(originalaudio)

with open('encrypted sample-6s.mp3','wb') as encrypted_file:
    encrypted_file.write(encrypted)

fernet=Fernet(key)
with open('encrypted sample-6s.mp3','rb') as enc_file:
    encrypted=enc_file.read()

decrypted=fernet.decrypt(encrypted)

with open('decrypted sample-6s.mp3','wb') as dec_file:
    dec_file.write(decrypted)

input()
print("DECRYPTION IS DONE!!!!")
input()
