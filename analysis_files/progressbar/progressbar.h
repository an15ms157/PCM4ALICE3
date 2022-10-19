#include <chrono>
#include <string>
using clk = std::chrono::steady_clock;

class ProgressBar{
    private:
    float progress_val = 0.0;
    int barWidth = 70;
    float step_variable = 0.1;
    clk::time_point t1; // begin
    clk::time_point t2; // end
    double Timestamp[10];
    int N_MAX;
    string loopname;

    public:

    ProgressBar(int MaxLimit, string Lname = "LOOPNAME" ){
        t1 = clk::now();
        for (int i = 1; i <= 9; i++) Timestamp[i] = ceil(MaxLimit*i*1./10);
        N_MAX = MaxLimit;
        loopname = Lname;
    }

    void progress(int iterator){
        //cout<< iterator <<"\t" << Timestamp[9]<< endl;

        double *position_counter = std::find(std::begin(Timestamp), std::end(Timestamp), iterator);
        if (position_counter != std::end(Timestamp)){ 
            progress_val += step_variable; 
            std::cout << "[";
            int pos = barWidth * progress_val;
            for (int i = 0; i < barWidth; i++) {
                if (i < pos) std::cout << "=";
                else if (i == pos) std::cout << ">";
                else std::cout << " ";
                }
            t2 = clk::now();
            auto d = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
            float time_difference = d.count() / 1000000.0;
            std::cout << "] " << int(progress_val * 100.0) <<" %\t"<< "Time: " <<  time_difference << "sec\r";

            std::cout.flush();
            std::cout << std::endl;
            }
        if (iterator ==  N_MAX) cout << "The loop for " << loopname << " has ended" << endl;    
    }
        
};