//RSA algorithm
#include <stdio.h>

int gcd(int a, int b) 
{
    if(b==0)
		return a;
	return gcd(b,a%b);
}

int mod_of_d(int e, int z) 
{
    int d = 1;
    while ((e * d) % z != 1) 
        d++;
        
    return d;
}

int modPower(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;

    for (int i = 0; i < exp; i++) {
        result = (result * base) % mod;
    }
    return result;
}

int main() 
{
    int p, q, n, z, d, e;
    int message;
    int encrypted, decrypted; 
    
    printf("Enter two prime numbers (p and q): ");
    scanf("%d %d", &p, &q);

    n = p * q;
    z = (p - 1) * (q - 1);

    printf("Enter a value for e (1 < e < %d) such that gcd(e, %d) = 1: ", z, z);
    scanf("%d", &e);

    if (gcd(e, z) != 1) 
	{
        printf("Invalid e! It must be coprime with %d.\n", z);
        return 1;
    }

    d = mod_of_d(e, z);

    printf("\nPublic Key: (%d, %d)", n, e);
    printf("\nPrivate Key: (%d, %d)\n", n, d);
    
    printf("Enter message to encrypt (as integer < %d): ", n);
    scanf("%d", &message);

    encrypted = modPower(message, e, n);
    printf("Encrypted message: %d\n", encrypted);

    decrypted = modPower(encrypted, d, n);
    printf("Decrypted message: %d\n", decrypted);

    return 0;
}
