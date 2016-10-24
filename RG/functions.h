/*
 * Author: David Ring
 * Desc: for including functions in main program ie function prototypes
 */

void read_dump(const char *filename);
//void calc_com();
//void calc_rg();
//void calc_re();
//void ave_re();
//void ave_rg();
void hist_rg();
void hist_re();
void unwrap();
double periodic(double dist, double coord, double L);
void write_traj(const char *filename);
void write_data(const char *filename);
int main(int argc, char *argv[]);
