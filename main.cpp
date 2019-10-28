/* main.cpp is the driver for a Conga line simulation.
 *
 * @author: Joel Adams, for CS 112 at Calvin University.
 *
 * Based on an exercise by Marc LeBlanc from Wheaton College (MS).
 */

#include "CongaLine.h"
#include "ListTester.h"

int main() {
    ListTester listTester;
    listTester.runTests();

	CongaLine dance("Ann", "Bob");
	dance.run();
}
