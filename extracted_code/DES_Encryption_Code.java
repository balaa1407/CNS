// Extracted from DES_Encryption_Code.pdf

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.util.Base64;
public class Main {
    public static void main(String[] args) throws Exception {
        KeyGenerator keygenerator = KeyGenerator.getInstance("DES");
        SecretKey secretKey = keygenerator.generateKey();
        String plaintext = "This is a secret message.";
        System.out.println("Original Text: " + plaintext);
        byte[] encryptedBytes = encrypt(plaintext.getBytes(), secretKey);
        String encryptedText = Base64.getEncoder().encodeToString(encryptedBytes);
        System.out.println("Encrypted Text (Base64): " + encryptedText);
        byte[] decryptedBytes = decrypt(encryptedBytes, secretKey);
        String decryptedText = new String(decryptedBytes);
        System.out.println("Decrypted Text: " + decryptedText);
    }
    public static byte[] encrypt(byte[] plaintext, SecretKey secretKey) throws Exception {
        Cipher cipher = Cipher.getInstance("DES/ECB/PKCS5Padding");
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);
        return cipher.doFinal(plaintext);
    }
    public static byte[] decrypt(byte[] ciphertext, SecretKey secretKey) throws Exception {
        Cipher cipher = Cipher.getInstance("DES/ECB/PKCS5Padding");
        cipher.init(Cipher.DECRYPT_MODE, secretKey);
        return cipher.doFinal(ciphertext);
    }
}
