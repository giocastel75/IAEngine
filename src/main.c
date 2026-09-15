#include <stdio.h>

#include "llama.h"
#include "ggml-backend.h"

int main(int argc, char *argv[])
{
    struct llama_model_params model_params;
    struct llama_model *model;

    printf("IAEngine v0.02\n");
    printf("--------------------------\n");
    fflush(stdout);

    if (argc < 2)
    {
        printf("Usage: IAEngine <model.gguf>\n");
        return 1;
    }

    printf("Model: %s\n\n", argv[1]);
    printf("Loading GGML backends...\n");
    fflush(stdout);

    ggml_backend_load_all();

    printf("Backends loaded.\n");
    printf("Loading GGUF model...\n\n");
    fflush(stdout);

    model_params = llama_model_default_params();

    /*
     * For now we keep the model on CPU.
     * Later we will study GPU offloading.
     */
    model_params.n_gpu_layers = 0;

    model = llama_model_load_from_file(
        argv[1],
        model_params
    );

    if (model == NULL)
    {
        printf("\nERROR: unable to load model.\n");
        return 1;
    }

    printf("\n--------------------------\n");
    printf("MODEL LOADED SUCCESSFULLY\n");
    printf("--------------------------\n");

    llama_model_free(model);

    printf("Model released.\n");

    return 0;
}