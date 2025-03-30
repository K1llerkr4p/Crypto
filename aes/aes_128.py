from Crypto.Cipher import AES
import binascii

def aes_128_encrypt(key: bytes, plaintext: bytes) -> bytes:
    cipher = AES.new(key, AES.MODE_ECB)
    return cipher.encrypt(plaintext)

def main():
    key_hex = "2b7e151628aed2a6abf7158809cf4f3c"
    plaintext_hex = "3243f6a8885a308d313198a2e0370734"
    
    key = binascii.unhexlify(key_hex)
    plaintext = binascii.unhexlify(plaintext_hex)
    
    ciphertext = aes_128_encrypt(key, plaintext)
    print("Ciphertext:", binascii.hexlify(ciphertext).decode())

if __name__ == "__main__":
    main()
