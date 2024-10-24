#include <stdio.h>
#include <string.h>
#include <omp.h>

#define LENGTH 1000

int count_words(const char *text)
{
    int count = 0;
    int in_word = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') // break word on gap
        {
            in_word = 0;
        }
        else
        {
            if (!in_word) // word if no gap
            {
                count++;
                in_word = 1;
            }
        }
    }
    return count;
}

int count_sentences(const char *text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') // break sentence
        {
            count++;
        }
    }
    return count;
}

int count_paragraphs(const char *text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '\n') // break para on new line
        {
            count++;
        }
    }

    if (count > 0 || text[0] != '\0') // if last para has no newline
    {
        count++;
    }
    return count;
}

int main()
{
    char text[LENGTH] = "Hello world! This is a sample text.\nThis has multiple sentences.\nAnd it also has multiple paragraphs.\nIT works";
    int word_count = 0, sent_count = 0, para_count = 0;
#pragma omp parallel sections
    {
#pragma omp section
        {
            word_count = count_words(text);
        }

#pragma omp section
        {
            sent_count = count_sentences(text);
        }

#pragma omp section
        {
            para_count = count_paragraphs(text);
        }
    }

    printf("Word count: %d\n", word_count);
    printf("Sentence count: %d\n", sent_count);
    printf("Paragraph count: %d\n", para_count);

    return 0;
}