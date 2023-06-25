/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
  Kp = Kpi;
  Ki = Kii;
  Kd = Kdi;
  output_lim_max = output_lim_maxi;
  output_lim_min = output_lim_mini;
  sum_cte = 0.0;
  diff_cte = 0,0;
  prev_cte = 0.0;
  cte = 0.0;
  delta_time = 0.0;

}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
  diff_cte = cte - prev_cte;
  sum_cte += cte;
  prev_cte = cte;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */

    double control = 0.0;

//   Check for 0 values for delta_time
    if (delta_time > 0) {
      double control = -Kp * prev_cte - Kd * diff_cte / delta_time - Ki * sum_cte;

    } else {
      // If dt is 0, set Kd to 0 too
      double control = -Kp * prev_cte - Ki * sum_cte;

    }
   //Super debug stack
    std::cout << '\n';
    std::cout << "Kp: "  << Kp << endl
              << "cte: " << cte << endl
              << "Kd: "  << Kd << endl
              << "diff_cte: "  << diff_cte << endl
              << "delta_time: "  << delta_time << endl
              << "Ki: "  << Ki << endl
              << "sum_cte: "  << sum_cte << endl
              << "Control: "  << control << endl;
    std::cout << '\n';


    if (control > output_lim_max) {
      control = output_lim_max;
    }     

    if (control < output_lim_min) {
      control = output_lim_min;
    }


    return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
  delta_time = new_delta_time;
}