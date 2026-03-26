#include "autocomplete.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_terms_lex(const void *a, const void *b)
{
    const struct term *ta = (const struct term *)a;
    const struct term *tb = (const struct term *)b;
    return strcmp(ta->term, tb->term);
}

static int compare_weight_desc(const void *a, const void *b)
{
    const struct term *ta = (const struct term *)a;
    const struct term *tb = (const struct term *)b;

    if (ta->weight < tb->weight) {
        return 1;
    }
    if (ta->weight > tb->weight) {
        return -1;
    }
    return strcmp(ta->term, tb->term);
}

static int starts_with(const char *word, const char *prefix)
{
    size_t n = strlen(prefix);
    return strncmp(word, prefix, n) == 0;
}

void read_in_terms(struct term **terms, int *pnterms, char *filename)
{
    FILE *fp;
    int expected_terms;
    int i;

    *terms = NULL;
    *pnterms = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        return;
    }

    if (fscanf(fp, "%d\n", &expected_terms) != 1 || expected_terms < 0) {
        fclose(fp);
        return;
    }

    *terms = malloc((size_t)expected_terms * sizeof(struct term));
    if (*terms == NULL) {
        fclose(fp);
        return;
    }

    for (i = 0; i < expected_terms; i++) {
        char line[1024];
        double weight;
        char text[200];

        if (fgets(line, sizeof(line), fp) == NULL) {
            break;
        }
        if (sscanf(line, "%lf\t%199[^\n]", &weight, text) != 2) {
            break;
        }

        (*terms)[i].weight = weight;
        strncpy((*terms)[i].term, text, sizeof((*terms)[i].term) - 1);
        (*terms)[i].term[sizeof((*terms)[i].term) - 1] = '\0';
    }

    *pnterms = i;
    fclose(fp);

    if (*pnterms > 1) {
        qsort(*terms, (size_t)*pnterms, sizeof(struct term), compare_terms_lex);
    }
}

int lowest_match(struct term *terms, int nterms, char *substr)
{
    int low = 0;
    int high = nterms - 1;
    int result = -1;
    size_t n;

    if (nterms <= 0) {
        return -1;
    }

    n = strlen(substr);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strncmp(terms[mid].term, substr, n);

        if (cmp < 0) {
            low = mid + 1;
        } else {
            if (starts_with(terms[mid].term, substr)) {
                result = mid;
            }
            high = mid - 1;
        }
    }

    return result;
}

int highest_match(struct term *terms, int nterms, char *substr)
{
    int low = 0;
    int high = nterms - 1;
    int result = -1;
    size_t n;

    if (nterms <= 0) {
        return -1;
    }

    n = strlen(substr);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strncmp(terms[mid].term, substr, n);

        if (cmp > 0) {
            high = mid - 1;
        } else {
            if (starts_with(terms[mid].term, substr)) {
                result = mid;
            }
            low = mid + 1;
        }
    }

    return result;
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr)
{
    int low;
    int high;
    int count;

    *answer = NULL;
    *n_answer = 0;

    low = lowest_match(terms, nterms, substr);
    if (low == -1) {
        return;
    }

    high = highest_match(terms, nterms, substr);
    if (high == -1 || high < low) {
        return;
    }

    count = high - low + 1;
    *answer = malloc((size_t)count * sizeof(struct term));
    if (*answer == NULL) {
        return;
    }

    memcpy(*answer, &terms[low], (size_t)count * sizeof(struct term));
    qsort(*answer, (size_t)count, sizeof(struct term), compare_weight_desc);
    *n_answer = count;
}
