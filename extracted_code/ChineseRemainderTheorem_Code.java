// Extracted from ChineseRemainderTheorem_Code.pdf

import java.math.BigInteger;
import java.util.Scanner;
public class ChineseRemainderTheorem {
    public static BigInteger solveCRT(BigInteger[] a, BigInteger[] m) {
        BigInteger M = BigInteger.ONE;
        for (BigInteger mi : m) {
            M = M.multiply(mi);
        }
        BigInteger solution = BigInteger.ZERO;
        for (int i = 0; i < a.length; i++) {
            BigInteger Mi = M.divide(m[i]);
            BigInteger Mi_inv = Mi.modInverse(m[i]);
            BigInteger term = a[i].multiply(Mi).multiply(Mi_inv);
            solution = solution.add(term);
        }
        return solution.mod(M);
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number of equations: ");
        int n = sc.nextInt();
        BigInteger[] a = new BigInteger[n];
        BigInteger[] m = new BigInteger[n];
        System.out.println("Enter the remainders (a_i) and moduli (m_i):");
        for (int i = 0; i < n; i++) {
            System.out.print("For equation " + (i + 1) + ", a_" + (i+1) + ": ");
            a[i] = sc.nextBigInteger();
            System.out.print("For equation " + (i + 1) + ", m_" + (i+1) + ": ");
            m[i] = sc.nextBigInteger();
        }
        BigInteger solution = solveCRT(a, m);
        BigInteger M = BigInteger.ONE;
        for (BigInteger mi : m) {
            M = M.multiply(mi);
        }
        System.out.println("\nThe solution is x ≡ " + solution + " (mod " + M + ")");
        sc.close();
    }
}
