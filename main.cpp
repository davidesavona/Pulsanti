#include <iostream>
#include "wiringPi.h"
#include "pthread.h"
#include "button.h"

#define DEFAULT_LOOP_TIME_NS 1000000L

button UP_BUTTON;
button DOWN_BUTTON;
button PID_BUTTON;
button GREEN_BUTTON;
bool pidButtonFlag=0;
bool greenButtonFlag=0;


timespec addition(timespec a, timespec b) {
    timespec r;

    if(a.tv_nsec + b.tv_nsec <= 999999999) {
        r.tv_nsec = a.tv_nsec + b.tv_nsec;
        r.tv_sec = a.tv_sec + b.tv_sec;
    }
    else {
        int c = (a.tv_nsec + b.tv_nsec)/1000000000;
        r.tv_nsec = a.tv_nsec + b.tv_nsec - 1000000000*c;
        r.tv_sec = a.tv_sec + b.tv_sec + c;
    }

    return r;
}




void *threadFunction(void* a) {

    //signal(SIGINT, myInterruptHandler);

    //readfromSM();

    struct timespec t_now;
    struct timespec t_next;
    struct timespec t_period;
    struct timespec t_wait;
    struct timespec pause_duration;

    //unsigned long int t_overflow = 0;   // measure the overflowed time for each cycle
    unsigned long int loop_count = 0;

    // t_period defines duration of one "running" cycle (1 ms in this case)
    t_period.tv_sec = 0;
    t_period.tv_nsec = DEFAULT_LOOP_TIME_NS;

    // pause_duration defines duration of pause considered when a buttton is pressed (1 s in this case)

    clock_gettime( CLOCK_MONOTONIC, &t_next);

    // Save into variables the first input variables from GUI
    // TODO: save user variables

    
    int Counter=0;
    while(1) {

       // chartclass.readButton();
        t_next = addition(t_next, t_period); // update t_next (needed for usleep at the end)clock_gettime ( CLOCK_MONOTONIC, &t_now);

        if(loop_count%1 == 0) {
            if(greenButtonFlag){
                if(UP_BUTTON.state()) { 
                    if(!pidButtonFlag) {
                        std::cout<<"Current UP"<<"\n";
                    }else{
                        std::cout<<"Cadence UP"<<"\n";
                    }
                }
                if(DOWN_BUTTON.state()) { 
                    if(!pidButtonFlag) {
                        std::cout<<"Current DOWN"<<"\n";
                    }else{
                        std::cout<<"Cadence DOWN"<<"\n";
                    }
                }
                if(PID_BUTTON.state()) { 
                    if(pidButtonFlag) {
                        pidButtonFlag=false;
                        std::cout<<"PID OFF"<<"\n";
                    }else{
                        pidButtonFlag=true;
                        std::cout<<"PID ON"<<"\n";
                    }
                }
            }
            if(GREEN_BUTTON.state()) { 
                if(greenButtonFlag) {
                    greenButtonFlag=false;
                    std::cout<<"STOP"<<"\n";
                }else{
                    greenButtonFlag=true;
                    std::cout<<"START"<<"\n";
                }
            }
            
            
        }
        if(loop_count%1000==0){ // 1 sec

        }




        loop_count++;

        clock_nanosleep ( CLOCK_MONOTONIC, TIMER_ABSTIME, &t_next, nullptr ); // waits until time t_next is reached

        // print t_now (just to check "running" cycle repeats with desired frequency)
        clock_gettime ( CLOCK_MONOTONIC, &t_now);
        //cout << "\nT running = " << t_now.tv_sec*1000 + t_now.tv_nsec/1000000 << "\n";
    }

}
int main(int, char**) {

    wiringPiSetup();
    UP_BUTTON.initButton(22);
    DOWN_BUTTON.initButton(23);
    PID_BUTTON.initButton(24);
    GREEN_BUTTON.initButton(25);
    //B.initButton(25);

    
    

    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, nullptr);
    pthread_join(thread, NULL);
    
 
    return 0;
}


