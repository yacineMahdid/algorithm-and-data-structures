def encrypt(message,key):
    # Variables Initalization
    encrypted_message = ""
    start = ord('a')
    end = ord('z')
    message = message.lower()

    # Iterate over each character
    for character in message:
        character = ord(character) # getting the ascii value

        if start <= character <= end:
            encrypted_character = chr((((character - start) + key) % 26) + start)
        else:
            encrypted_character = chr(character)
        encrypted_message = encrypted_message + encrypted_character
    print(encrypted_message)


def decrypt(message,key):
    encrypt(message,26-key)


encrypt("Abcdefg",4)
decrypt("efghijk",4)