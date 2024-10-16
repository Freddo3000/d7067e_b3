int scmp( unsigned char *s1, unsigned char *s2 )
{
    while( *s1 != '\0' && *s1 == *s2 )
    {
        s1++;
        s2++;
    }
    return( *s1-*s2 );
}

int
cmpit(unsigned char **h1, unsigned char **h2)
{
    return( scmp(*h1, *h2) );
}
