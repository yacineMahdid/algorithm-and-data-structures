def encrypt(message,key):
    encrypted_message = ""
    start = ord('a')
    end = ord('z')
    for character in message:
        character = ord(character)
        if start <= character <= end:
            encrypted_character = chr((((character - start) + key) % 26) + start)
        else:
            encrypted_character = chr(character)
        encrypted_message = encrypted_message + encrypted_character
    print(encrypted_message)


def decrypt(message,key):
    encrypt(message,26-key)


encrypt("test haha",7)
decrypt("alza ohoh",7)