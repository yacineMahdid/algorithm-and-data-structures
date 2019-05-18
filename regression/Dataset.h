class Dataset{
    public:
        float **X;
        float *y;
        int number_predictor;
        int length;

        Dataset();
        Dataset(float **X_train,float *y_train, int length_train, int number_predictor_train);
        Dataset(const Dataset &data);
        ~Dataset();
};