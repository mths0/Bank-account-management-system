int loadAccounts(Account accounts[])
{

    FILE *file = fopen("Accounts.bin", "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }
    size_t count = fread(&accounts[0], sizeof(Account), 1, file);
    return count; /*number of accounts loaded.*/
    fclose(file);
}
