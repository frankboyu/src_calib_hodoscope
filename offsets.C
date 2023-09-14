void GetData(TString fname, double *y, const int N) {
    ifstream fin(fname);
    double prod = 0.0; double sum = 0.0;
    for (int i = 0; i < N; i++) {
        char sep; int n; double w, t, dt, sigma;
        fin >> n >> sep >> w >> sep >> t >> sep >> dt >> sep >> sigma;
        y[i] = t;
        if (sigma < 0.06 && t != 0.0) {
            y[i] = 0.0;
            cout << "Bad fit: counter " << n << endl;
        }
    }
    fin.close();
}
void GetCCDBOffsetsBase(double &adc_offset, double &tdc_offset) {
    ifstream fin("base-time-offsets-ccdb.txt");
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    fin >> adc_offset >> tdc_offset;
    fin.close();
}
void GetCCDBOffsetsTDC(double* tdc_offsets, const int N) {
    ifstream fin("tdc-time-offsets-ccdb.txt");
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int n;
    for (int i = 0; i < N; i++) {
        fin >> n >> tdc_offsets[i];
    }
    fin.close();
}
void GetCCDBOffsetsADC(double* adc_offsets, const int N) {
    ifstream fin("adc-time-offsets-ccdb.txt");
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int n;
    for (int i = 0; i < N; i++) {
        fin >> n >> adc_offsets[i];
    }
    fin.close();
}
void WriteBaseOffsets(double c1_adc, double c1_tdc, int run_numb) {
    double adc_ccdb; double tdc_ccdb;
    GetCCDBOffsetsBase(adc_ccdb,tdc_ccdb);
    char file_name[300];
    sprintf(file_name,"base-time-offsets-new.txt");
    ofstream fout; fout.open(file_name);
    TString sep = "        ";
    fout << adc_ccdb - c1_adc << sep << tdc_ccdb - c1_tdc << endl;
    fout.close();
}
void WriteTAGHTDCOffsets(double *y, const int N, double &c1_tdc, int run_numb) {
    double y_ccdb[N];
    GetCCDBOffsetsTDC(y_ccdb,N);
    char file_name[300];
    sprintf(file_name,"tdc-time-offsets-new.txt");
    ofstream fout; fout.open(file_name);
    TString sep = "        ";
    for (int i = 0; i < N; i++) {
        double offset = y_ccdb[i] + y[i];
        if (i == 0) c1_tdc = offset;
        if (y_ccdb[i] == 0.0 && y[i] == 0.0) {
            offset = 0.0;
        } else {
            offset -= c1_tdc;
        }
        fout << i + 1 << sep << offset << endl;
    }
    fout.close();
    //fout.open("new_offsets.txt");
    //for (int i = 0; i < N; i++) fout << i + 1 << sep << y[i] << endl;
    //fout.close();
}
void WriteTAGHADCOffsets(double *y_tdcadc, double *y, const int N, double &c1_adc, int run_numb) {
    double y_ccdb[N];
    GetCCDBOffsetsADC(y_ccdb,N);
    char file_name[300];
    sprintf(file_name,"adc-time-offsets-new.txt");
    ofstream fout; fout.open(file_name);
    TString sep = "        ";
    for (int i = 0; i < N; i++) {
        double offset = y_ccdb[i] + y[i] - y_tdcadc[i];
        if (i == 0) c1_adc = offset;
        if (y_ccdb[i] == 0.0 && y[i] == 0.0) {
            offset = 0.0;
        } else {
            offset -= c1_adc;
        }
        fout << i + 1 << sep << offset << endl;
    }
    fout.close();
    //fout.open("fadc_time_offsets_diff.txt");
    //for (int i = 0; i < N; i++) fout << i + 1 << sep << y[i] - y_tdcadc[i] << endl;
    //fout.close();
}
int offsets(int run_numb) {
    //system("mkdir -p offsets");
    // TAGH offsets
    const int N = 274; // counters
    double y[N]; double c1_tdc = 0.0; double c1_adc = 0.0;
    GetData("results_TAGH.txt",y,N);
    WriteTAGHTDCOffsets(y,N,c1_tdc, run_numb);
    double y_tdcadc[N];
    GetData("results_TDCADC.txt",y_tdcadc,N);
    WriteTAGHADCOffsets(y_tdcadc,y,N,c1_adc, run_numb);
    WriteBaseOffsets(c1_adc,c1_tdc, run_numb);
    return 0;
}
