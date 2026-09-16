#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "llama.h"
#include "ggml-backend.h"

int main(int argc, char *argv[])
{
    struct llama_model_params model_params;
    struct llama_model *model;
    const struct llama_vocab *vocab;

    const char *text;
    int text_len;

    llama_token *tokens;
    int32_t n_tokens;
    int32_t capacity;
    int32_t i;

    char piece[256];
    int32_t piece_len;

    printf("IAEngine v0.04 - Tokenizer Inspector\n");
    printf("------------------------------------\n\n");

    if (argc < 2)
    {
        printf("Usage: IAEngine <model.gguf>\n");
        return 1;
    }

    /*
     * Test text.
     * Later we will read this from keyboard.
     */
    text = "Ciao, come stai?";
    text_len = (int) strlen(text);

    printf("Input text:\n%s\n\n", text);

    /*
     * Initialize llama.cpp / GGML.
     */
    ggml_backend_load_all();

    model_params = llama_model_default_params();
    model_params.n_gpu_layers = 0;

    printf("Loading model...\n");

    model = llama_model_load_from_file(
        argv[1],
        model_params
    );

    if (model == NULL)
    {
        printf("ERROR: unable to load model.\n");
        return 1;
    }

    printf("Model loaded.\n\n");

    /*
     * Get the vocabulary/tokenizer associated with the model.
     */
    vocab = llama_model_get_vocab(model);

    /*
     * Allocate more than enough space for our small test string.
     */
    capacity = text_len + 16;

    tokens = (llama_token *) malloc(
        sizeof(llama_token) * capacity
    );

    if (tokens == NULL)
    {
        printf("ERROR: unable to allocate token buffer.\n");
        llama_model_free(model);
        return 1;
    }

    /*
     * Tokenize.
     *
     * add_special   = true
     * parse_special = false
     */
    n_tokens = llama_tokenize(
        vocab,
        text,
        text_len,
        tokens,
        capacity,
        true,
        false
    );

    if (n_tokens < 0)
    {
        printf("ERROR: token buffer too small.\n");
        free(tokens);
        llama_model_free(model);
        return 1;
    }

    printf("Number of tokens: %d\n\n", (int) n_tokens);

    printf("TOKEN LIST\n");
    printf("------------------------------------\n");

    for (i = 0; i < n_tokens; i++)
    {
        piece_len = llama_token_to_piece(
            vocab,
            tokens[i],
            piece,
            sizeof(piece) - 1,
            0,
            true
        );

        if (piece_len >= 0)
        {
            piece[piece_len] = '\0';

            printf(
                "Token %2d | ID %6d | \"%s\"\n",
                (int) i,
                (int) tokens[i],
                piece
            );
        }
        else
        {
            printf(
                "Token %2d | ID %6d | <unable to decode>\n",
                (int) i,
                (int) tokens[i]
            );
        }
    }

    printf("------------------------------------\n");

    free(tokens);
    llama_model_free(model);

    printf("\nDone.\n");

    return 0;
}