#include <stdio.h>

#include "llama.h"
#include "ggml-backend.h"

int main(int argc, char *argv[])
{
    struct llama_model_params model_params;
    struct llama_model *model;
    const struct llama_vocab *vocab;
    char description[256];

    printf("IAEngine v0.03 - Model Inspector\n");
    printf("--------------------------------\n\n");

    if (argc < 2)
    {
        printf("Usage: IAEngine <model.gguf>\n");
        return 1;
    }

    printf("Loading model:\n%s\n\n", argv[1]);

    ggml_backend_load_all();

    model_params = llama_model_default_params();

    /* CPU only for now */
    model_params.n_gpu_layers = 0;

    model = llama_model_load_from_file(
        argv[1],
        model_params
    );

    if (model == NULL)
    {
        printf("ERROR: unable to load model.\n");
        return 1;
    }

    printf("\nMODEL LOADED\n");
    printf("--------------------------------\n");

    vocab = llama_model_get_vocab(model);

    description[0] = '\0';
    llama_model_desc(model, description, sizeof(description));

    printf("Description       : %s\n", description);
    printf("Parameters        : %llu\n",
           (unsigned long long) llama_model_n_params(model));

    printf("Model size        : %llu bytes\n",
           (unsigned long long) llama_model_size(model));

    printf("Training context  : %d tokens\n",
           (int) llama_model_n_ctx_train(model));

    printf("Embedding size    : %d\n",
           (int) llama_model_n_embd(model));

    printf("Transformer layers: %d\n",
           (int) llama_model_n_layer(model));

    printf("Attention heads   : %d\n",
           (int) llama_model_n_head(model));

    printf("KV heads          : %d\n",
           (int) llama_model_n_head_kv(model));

    printf("Vocabulary size   : %d tokens\n",
           (int) llama_vocab_n_tokens(vocab));

    printf("--------------------------------\n");

    llama_model_free(model);

    printf("\nModel released.\n");

    return 0;
}