# CancerTreatmentPlanningTool

We made a program that makes finding cancer treatment facilities easy.

Our program takes into account your state of residency and type of insurance in order to:
-Find the cheapest treatment center, incl. Airfare and treatment cost
-Learn the survival rates of cancer by state

Basic Implementation

Utilizing a stack:
1) allocate stack based on user-defined size.  Cheapest treatment = top, descending down
2) peek at top element of stack
3) if user wants to see more, pop off that element and repeat steps 2-3, continuing to show next cheapest treatment


Utilizing a heap with a priority queue for airfare:
1) Assigns a higher priority based on a lower cost
2) Searches for the cheapest airfare to a location close to the selected treatment center


Utilizing a linked list for users saved treatment plans
1) A node will be added with the state, cost, and treatment success rate if the user decides they might want to use the plan
2) Options saved can be printed so that the user may compare plans side by side





