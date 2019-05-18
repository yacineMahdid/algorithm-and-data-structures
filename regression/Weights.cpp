#include "utils.h"

class Weights{
    private:
        int MAX_WEIGHTS;

    public:
        float* values;
        int number_weights;

        Weights(){

        }

        Weights(int number_predictor, int random_init){
            // Random Init Variables
            MAX_WEIGHTS = 100;
            srand(time(0));  // random number generator

            number_weights = number_predictor + 1; // +1 for the intercept
            values = (float *) std::malloc(sizeof(float)*number_weights);
            for(int i=0; i<number_weights; i++){
                if(random_init){
                    values[i] = (rand() % MAX_WEIGHTS);
                }else{
                    values[i] = 0;
                }
            }
        }

        ~Weights(){
            free(values);
        }

        void update(Dataset data, float *y_pred, float learning_rate){
            float multiplier = learning_rate/data.length;
            // Update each weights
            for(int i = 0; i < number_weights; i++){
                values[i] = values[i] - multiplier*(sum_residual(data.X[i],data.y,y_pred,data.length));
            }
        }
};