#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string encrypt(string plaintext, string key);
bool validate_key(string key);

int main(int argc, string argv[])
{
    // Check for key in command-line
    if (argc != 2)
    {
        printf("ERROR: Usage: ./substitution [key]\n");
        return 1;
    }

    string key = argv[1];

    // Validate key
    if (!validate_key(key))
    {
        return 1;
    }

    // Get message from user
    string user_input = get_string("plaintext:\t");

    // Encrypt message
    string cipher = encrypt(user_input, key);

    // Print ciphertext
    printf("ciphertext:\t%s\n", cipher);

    return 0;
}

bool validate_key(string key)
{
    // Create 26-int array to track character repetition
    // Initialize each element to 0
    int char_count[26];
    for (int i = 0; i < 26; i++)
    {
        char_count[i] = 0;
    }

    int i = 0, curr_index = 0;
    while (key[i] != '\0')
    {
        // Key must be all alphabetical characters
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetical characters.\n");
            return false;
        }

        // Test for repeat characters by keeping track of already-seen letters in char_count array
        // Index in char_count array = given character's offset from beginning of alphabet (so every element should be 1)
        if (isupper(key[i]))
        {
            curr_index = key[i] - 'A';
            char_count[curr_index]++;

            // If letter appears more than once, key is invalid
            if (char_count[curr_index] > 1)
            {
                printf("Key cannot contain repeated characters.\n");
                return false;
            }
        }
        if (islower(key[i]))
        {
            curr_index = key[i] - 'a';
            char_count[curr_index]++;

            // If letter appears more than once, key is invalid
            if (char_count[curr_index] > 1)
            {
                printf("Key cannot contain repeated characters.\n");
                return false;
            }
        }
        i++;
    }

    // Ensure key has 26 characters
    if (i != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }
    // If none of the above return false, key is valid
    return true;
}

string encrypt(string plaintext, string key)
{
    // Create two key arrays: one for uppercase letters and one for lowercase letters
    char upper_key[26];
    char lower_key[26];

    for (int i = 0; i < 26; i++)
    {
        upper_key[i] = toupper(key[i]);
        lower_key [i] = tolower(key[i]);
    }
    // Encrypt each alphabetical character in plaintext by looking up proper mapping in key arrays
    string ciphertext = plaintext;
    int i = 0, index;
    while (plaintext[i] != '\0')
    {
        if (isupper(plaintext[i]))
        {
            // Lookup mapping in key array & copy encrypted character to ciphertext string
            index = plaintext[i] - 'A';
            ciphertext[i] = upper_key[index];
        }
        if (islower(plaintext[i]))
        {
            // Lookup mapping in key array & copy encrypted character to ciphertext string
            index = plaintext[i] - 'a';
            ciphertext[i] = lower_key[index];
        }
        i++;
    }
    return ciphertext;
}
