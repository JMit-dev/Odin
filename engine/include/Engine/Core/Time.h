#ifndef TIME_H
#define TIME_H

namespace Engine {
class Time {
public:
  static void init();
  static float frame(); // returns /\ t in seconds
  static float total(); // seconds since app start
private:
  static double s_last, s_now;
};
} // namespace Engine
#endif
