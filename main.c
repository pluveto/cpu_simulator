
#include "require.h"
#include "type/memory_man.h"
#include "type/simulator.h"
/**
 * @define MEMORY_SIZE 模拟电脑的内存大小
 */

#define MEMORY_SIZE (32 * 1024)

int main(int argc, char **argv) {
  pSimulator simulator = SimulatorConstruct();
  simulator->init("Simulator I", MEMORY_SIZE);
  simulator->load("dict.dic");
  simulator->run();
  simulator->display();
  simulator_free(simulator);
  return 0;
}