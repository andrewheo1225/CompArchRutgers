
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void printTheStatement(char *phrase)
{
    printf("%s", phrase);
}
struct cacheLL
{

    long int tag;
    long int lruTag;
    int num;
    struct cacheLL
        *prev;
    struct cacheLL
        *next;
};

struct cacheLL *createcacheLL(struct cacheLL *n, struct cacheLL *p, long int t, int number)
{

    struct cacheLL
        *cur = (struct cacheLL
                    *)calloc(1, sizeof(struct cacheLL));
    struct cacheLL *secondPtr = (struct cacheLL
                                     *)calloc(1, sizeof(struct cacheLL));
    if (!cur)
    {
        free(secondPtr);
        return NULL;
    }

    secondPtr->next = n;
    secondPtr->prev = p;
    cur->next = n;
    cur->tag = t;
    secondPtr->tag = t;
    cur->lruTag = number;
    secondPtr->lruTag = number;
    cur->num = number;
    cur->prev = p;
    secondPtr->num = number;
    free(secondPtr);
    return cur;
}

int base2log(int num)
{
    int answer = 0;
    while (num >>= 1)
    {
        answer++;
    }
    return answer;
}

int stringtoint(char *string)
{

    int start = 0;
    int end = 0;
    int result = 0;
    int cache = -1;
    while (string[start] != '\0')
    {
        start++;
        cache++;
    }
    while (end < start)
    {
        result = result * 10;
        cache += result;
        result += (int)(string[end]);
        result = result - 48;
        end++;
    }

    return result;
}

int path(int block_soze, int cache_size, int count, struct cacheLL **ll_cache,
         long int hexdecAddress, int replacement_policy, int sfa)
{

    if (ll_cache == NULL)
        return 1;
    int target = 2;
    int answer = 1;
    long int blockOffset;
    long int ILocation;
    long int tagLocation;
    blockOffset = hexdecAddress % block_soze;
    long int brancj = (hexdecAddress - blockOffset) % (cache_size * block_soze);
    ILocation = brancj / block_soze;
    tagLocation = hexdecAddress - blockOffset - (ILocation * cache_size * block_soze);
    int dummy_storage = 0;
    int total = 0;
    target--;

    struct cacheLL
        *storage;
    struct cacheLL
        *begin = ll_cache[ILocation];
    struct cacheLL *cachediff;
    int *cachestorage = calloc(1, sizeof(int *) * count);
    struct cacheLL
        *prior = NULL;
    struct cacheLL
        *cur = begin;

    for (int i = 0; i < count; i++)
    {
        cachestorage[i] = count;
    }
    for (; cur != NULL; cur = cur->next)
    {
        if (dummy_storage != 1 && target == 1)
        {
            if (cur->tag == tagLocation)
            {
                if (replacement_policy == 1 && cur != NULL)
                {
                    free(cachestorage);
                    return 0;
                }
                else if (sfa != 1)
                {
                    prior->next = cur->next;
                    if (cur->next != NULL)
                    {
                        struct cacheLL
                            *temp = cur->next;

                        temp->prev = prior;
                    }
                    storage = cur;
                    storage->next = NULL;
                       cachediff = cur;
                    cachediff->next = NULL;
                    dummy_storage = 1;
                }
            }
        }
        if (cur->num > total)
            total = cur->num;

        prior = cur;
    }
    target++;
    free(cachediff);
    if (dummy_storage == 1 && sfa != 1 && target == 2)
    {
        prior->next = storage;
        storage->prev = prior;
        free(cachestorage);
        storage->num = total;
        storage->next = NULL;

        return 0;
    }

    total += 2;
    total -= 1;

    struct cacheLL
        *newCache = createcacheLL(NULL, prior, tagLocation, total);
    prior->next = newCache;
    if (total > count)
    {
        storage = begin->next;
        cur = storage->next;
        free(storage);
        begin->next = cur;
        cur->prev = begin;
    }
    free(cachestorage);
    return answer;
}
void initialFree(struct cacheLL *ptr)
{
    struct cacheLL
        *prev = ptr;

    while (ptr != NULL)
    {
        ptr = ptr->next;

        free(prev);
        prev = ptr;
    }
}
void clearString(char *array, int size)
{
    for (int i = 0; i < size; size++)
    {
        array[i] = ' ';
    }
}
void freeAll(struct cacheLL **cache, int size)
{

    if (cache == NULL)
        return;
    int start = 0;
    while (start < size)
    {
        initialFree(cache[start]);
        start++;
    }
    free(cache);
}
void printStatements(int one, int two, int three, int four)
{
    int *storagefourVar = calloc(1, sizeof(int *) * 4);

    printf("Memory reads: %d\n", one);
    storagefourVar[0] = one;

    printf("Memory writes: %d\n", two);
    storagefourVar[1] = two;

    printf("Cache hits: %d\n", three);
    storagefourVar[2] = three;

    printf("Cache misses: %d\n", four);

    storagefourVar[3] = four;
    free(storagefourVar);
}
int main(int argc, char **argv)
{

    int cache_power = 0;
    int fifo_lru;
    int cache_size = 0;
    int hashing = 0;
    int block_soze = 0;
    int cap = 0;
    int assoc;
    int power_block = 0;
    int line;
    int sets_num;
    int size = 0;
    size = 0;
    while (argv[5][size] != '\0')
    {
        size++;
        hashing++;
    }
    size++;
    char *file = (char *)malloc(sizeof(char *) * size);
    strcpy(file, argv[5]);
    FILE *fp;
    fp = fopen(file, "r");

    if (!fp)
    {
        free(file);
        return 1;
    }
    free(file);
    block_soze = stringtoint(argv[4]);
    power_block = base2log(block_soze);
    if (power_block == -1)
        return 1;
    cache_size = stringtoint(argv[1]);
    cache_power = base2log(cache_size);
    if (cache_power == -1)
        return 1;
    if (strcmp("lru", argv[3]) == 0)
    {
        fifo_lru = 2;
    }
    else
    {
        fifo_lru = 1;
    }
    hashing = 0;
    int letters;
    letters = 0;
    while (argv[2][letters] != '\0')
    {
        letters++;
    }
    if (letters == 5)
    {
        sets_num = 1;
        line = cache_size / block_soze;
        assoc = 1;
    }
    else if (letters == 6)
    {
        line = 1;
        sets_num = cache_size / block_soze;
        assoc = 0;
    }
    else
    {
        int digit = letters;
        digit = digit - 6;
        char *trash = (char *)calloc(1, sizeof(char) * digit + 1);
        cap = 6;
        while (argv[2][cap] != '\0')
        {
            trash[cap - 6] = argv[2][cap];
            cap++;
        }
        trash[cap - 6] = '\0';
        assoc = stringtoint(trash);

        if (base2log(assoc) == -1)
        {
            free(trash);
            return -1;
        }

        free(trash);
        line = assoc;
        sets_num = cache_size / (block_soze * assoc);
    }
    struct cacheLL
        **prefetch = (struct cacheLL
                          **)calloc(1, sizeof(struct cacheLL
                                                  *) *
                                           sets_num);
    struct cacheLL
        **withoutPrefetch = (struct cacheLL
                                 **)calloc(1, sizeof(struct cacheLL
                                                         *) *
                                                  sets_num);

    letters = 0;
    hashing = 0;
    while (letters < sets_num)
    {
        struct cacheLL
            *b = createcacheLL(NULL, NULL, -1, 0);
        struct cacheLL
            *a = createcacheLL(NULL, NULL, -1, 0);

        prefetch[letters] = b;
        withoutPrefetch[letters] = a;
        letters++;
        hashing++;
    }

    char *programcounter = (char *)calloc(1,sizeof(char) * 100);
    int prefetchhit = 0;
    int woprefetchread = 0;
    int prefetchmiss = 0;
    int woprefetchHit = 0;
    int prefetchwrite = 0;
    int woprefetchmiss = 0;
    int prefechread = 0;
    int woprefetchwrite = 0;
    char i = 'a';
    long int hexadecimalAddress = 0;
    char *cachestring = calloc(1, sizeof(char *) * sets_num);
    char *offsettCache = calloc(1, sizeof(char *) * sets_num);

    while (fscanf(fp, "%s ", programcounter) == 1)
    {
        if (strcmp("#eof", programcounter) == 0)
            break;
        if (fscanf(fp, "%c %lx", &i, &hexadecimalAddress) != 2)
        {
            free(cachestring);
            free(offsettCache);
            return 1;
        }
        if (path(block_soze, sets_num, line, withoutPrefetch, hexadecimalAddress, fifo_lru, 0) == 0)
        {
            switch (i)
            {
            case 'W':
                woprefetchwrite++;
                break;
            }

            for (int i = 0; i < sets_num; i++)
            {
                cachestring[i] = i;
            }
            woprefetchHit++;
        }
        else
        {
            woprefetchmiss++;
            switch (i)
            {
            case 'R':
                woprefetchread++;
                break;

            default:
                woprefetchread++;
                woprefetchwrite++;
            }
      
        }

        if (path(block_soze, sets_num, line, prefetch, hexadecimalAddress, fifo_lru, 0) == 0)
        {
            prefetchhit++;
            switch (i)
            {
            case 'W':
                prefetchwrite++;
                break;
            }
         
        }
        else
        {
            for (int i = 0; i < sets_num; i++)
            {
                offsettCache[i] = i;
            }
            prefetchmiss++;
            switch (i)
            {
            case 'R':
                prefechread++;
                break;

            default:
                prefechread++;
                prefetchwrite++;
            }

            int flagNOW = 0;
            if (path(block_soze, sets_num, line, prefetch, hexadecimalAddress + block_soze, fifo_lru, 1) != flagNOW)
            {
                prefechread++;
            }

        }
    }

    printTheStatement("Prefetch 0\n");
    printStatements(woprefetchread, woprefetchwrite, woprefetchHit, woprefetchmiss);
    printTheStatement("Prefetch 1\n");
    printStatements(prefechread, prefetchwrite, prefetchhit, prefetchmiss);
    freeAll(withoutPrefetch, sets_num);
    freeAll(prefetch, sets_num);
    free(programcounter);
    free(cachestring);
    fclose(fp);
    free(offsettCache);
    return 0;
}
