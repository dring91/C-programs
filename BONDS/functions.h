/*
 * Author: David Ring
 * Desc: for including functions in main program ie function prototypes
 */

void read_dump(const char *filename);
void unwrap();
double periodic(double dist, double coord, double L);
void write_traj(const char *filename);
void write_data(const char *filename);
int main(int argc, char *argv[]);
