#include "Test.h"

// Test Functions
Test::Test() {
    srand (time(NULL));
    goalState = new Point2D(20,20);
    min_heap = new PriorityQueue();
    a_star = new AStar(obs, *goalState, 50, 50);
    test_point_set_comparator_equals();
    // test_push();
    // test_pop();
    // test_contains();
    // test_update();
    // test_a_star_adjacent();
    // test_a_star_init();

}

Test::~Test() {
    delete min_heap;
    delete goalState;
    delete a_star;
}


///////////////////////////////////////////
// Test AStar Class  //////////////////////
///////////////////////////////////////////
void Test::test_a_star_init() {
    a_star->testHelper(true,true,true);
}


void Test::test_a_star_adjacent(){
    // // Middle
    std::list<State*>* adjacent_list = a_star->getAdjacent(new State(*(new Point2D(20,25)), *goalState, 1, NULL));
    // Top
    std::list<State*>* adjacent_list2 = a_star->getAdjacent(new State(*(new Point2D(20,50)), *goalState, 1, NULL));
    // Left
    std::list<State*>* adjacent_list3 = a_star->getAdjacent(new State(*(new Point2D(50,25)), *goalState, 1, NULL));
    // Right
    std::list<State*>* adjacent_list4 = a_star->getAdjacent(new State(*(new Point2D(0,25)), *goalState, 1, NULL));
    // Bottom
    std::list<State*>* adjacent_list5 = a_star->getAdjacent(new State(*(new Point2D(20,0)), *goalState, 1, NULL));
    // Top-Left
    std::list<State*>* adjacent_list6 = a_star->getAdjacent(new State(*(new Point2D(50,50)), *goalState, 1, NULL));
    // Top-Right
    std::list<State*>* adjacent_list7 = a_star->getAdjacent(new State(*(new Point2D(0,50)), *goalState, 1, NULL));
    // Bot-Right
    std::list<State*>* adjacent_list8 = a_star->getAdjacent(new State(*(new Point2D(0,0)), *goalState, 1, NULL));
    // Bot-Left
    std::list<State*>* adjacent_list9 = a_star->getAdjacent(new State(*(new Point2D(50,0)), *goalState, 1, NULL));
    
    std::cout << "Should be 8... " << adjacent_list->size() << "\n";
    std::cout << "Should all be 5... " << adjacent_list2->size() << ", "<< adjacent_list3->size() << ", "<< adjacent_list4->size() << ", "<< adjacent_list5->size() << "\n";
    std::cout << "Should all be 3... " << adjacent_list6->size() << ", "<< adjacent_list7->size() << ", "<< adjacent_list8->size() << ", "<< adjacent_list9->size() << "\n";
    // for (auto x : *adjacent_list)
    //     std::cout << *x;

    delete adjacent_list;
    delete adjacent_list2;
    delete adjacent_list3;
    delete adjacent_list4;
    delete adjacent_list5;
    delete adjacent_list6;
    delete adjacent_list7;
    delete adjacent_list8;
    delete adjacent_list9;
}




///////////////////////////////////////////
// Test PriorityQueue Class  //////////////
///////////////////////////////////////////
void Test::test_push() {
    for (int i = 0; i < 10; ++i) {
        State* state = new State(*(new Point2D(i,i+1)), *goalState, 1, NULL);
        min_heap->push(state);
    }
    min_heap->printQueue();
}
void Test::test_pop() {
    for (int i = 0; i < 4; ++i) {
        curState = min_heap->pop();
        std::cout << "... Popped: " << *curState;
    }
    std::cout << "---------------------------\n";
    std::cout << "Printing rest of queue\n";
    std::cout << "---------------------------\n\n";
    min_heap->printQueue();
}
void Test::test_update() {
    min_heap->printQueue();
    std::cout << "-------- Test: Update on (4,5) --------\n";
    State* state = new State(*(new Point2D(4,5)), *goalState, 4, NULL);
    min_heap->update(*state, *goalState);
    min_heap->printQueue();
    delete state;

}
void Test::test_contains() {
    State* state = new State(*(new Point2D(2,3)), *goalState, 4, NULL);
    std::cout << "\n---------------------------\n";
    std::cout << "Check to see if queue contains (2,3) w/ diff g\n";
    if (min_heap->contains(*state))
        std::cout << "YEAH BUDDY!!!! we got it!";
    else std::cout << "nooooooooooooooooo\n";
    std::cout << "\n---------------------------\n\n";

    State* state_two = new State(*(new Point2D(19,3)), *goalState, 4, NULL);
    std::cout << "\n---------------------------\n";
    std::cout << "Check to see if queue doesn't contain (19,3) w/ diff g\n";
    if (min_heap->contains(*state_two))
        std::cout << "Uh oh";
    else std::cout << "Not Found !!! Holla!";
    std::cout << "\n---------------------------\n\n";

    delete state;
    delete state_two;
}

///////////////////////////////////////////
// Test State Class Functions /////////////
///////////////////////////////////////////
void Test::test_state_comparator_equals(){
    Point2D* goalState = new Point2D(20,20);
    std::set<State,state_set_comparator>* state_set = new std::set<State,state_set_comparator>();
    
    // Inject First Set
    for (int i = 0; i < 10; i++) {
        State* state = new State(*(new Point2D(i,i+1)), *goalState, 1, NULL);
        state_set->insert(*state);
        delete state;
    }
    for (auto x : *state_set)
        std::cout << x;
    std::cout << "---------------------------\n";
    std::cout << "Size of obstacle_set: " << state_set->size() << "\n";
    std::cout << "---------------------------\n\n";

    // Inject Second Set
    for (int i = 0; i < 10; i++) {
        State* state = new State(*(new Point2D(i,i+1)), *goalState, 1, NULL);
        state_set->insert(*state);
        delete state;
    }
    for (auto x : *state_set)
        std::cout << x;
    std::cout << "---------------------------\n";
    std::cout << "Size of obstacle_set: " << state_set->size() << "\n";
    std::cout << "---------------------------\n\n";
    
    delete goalState;
    delete state_set;
}

void Test::test_state_2dpoint_compare(){

}

///////////////////////////////////////////
// Test 2D Comparator /////////////////////
///////////////////////////////////////////
void Test::test_point_set_comparator_increasing(){
    // insert point 2's and print
    for (int i = 0; i < 10; i++) {
        Point2D* point = new Point2D(i,i+1);
        obstacle_set.insert(*point);
        delete point;
    }

    for (auto x : obstacle_set)
        std::cout << "Point: (" << x.x << ", " << x.y << ")\n";
}

void Test::test_point_set_comparator_equals(){
    Point2D* t_point1 = new Point2D(77, 77);
    Point2D* t_point1_ = new Point2D(77, 77);
    Point2D* t_point2 = new Point2D(86, 21);
    Point2D* t_point2_ = new Point2D(86, 21);
    Point2D* t_point3 = new Point2D(87, 21);
    Point2D* t_point3_ = new Point2D(87, 21);
    Point2D* t_point4 = new Point2D(21, 86);
    Point2D* t_point4_ = new Point2D(21, 86);
    Point2D* t_point5 = new Point2D(20, 86);
    Point2D* t_point5_ = new Point2D(20, 86);
    obstacle_set.insert(*t_point1);
    obstacle_set.insert(*t_point2);
    obstacle_set.insert(*t_point3);
    obstacle_set.insert(*t_point4);
    obstacle_set.insert(*t_point5);
    obstacle_set.insert(*t_point1_);
    obstacle_set.insert(*t_point2_);
    obstacle_set.insert(*t_point3_);
    obstacle_set.insert(*t_point4_);
    obstacle_set.insert(*t_point5_);

    int arr1 [10];
    int arr2 [10];
    for (int i = 0; i < 10; ++i) {
        int newNum = rand() % 50;
        int newNum2 = rand() % 50;
        arr1[i] = newNum;
        arr2[i] = newNum2;
        Point2D* t_point = new Point2D(newNum, newNum2);
        obstacle_set.insert(*t_point);
        delete t_point;
    }
    std::cout << "---------------------------\n";
    for (auto x : obstacle_set)
        std::cout << "Point: (" << x.x << ", " << x.y << ")\n";
    std::cout << "---------------------------\n";
    std::cout << "Size of obstacle_set: " << obstacle_set.size() << "\n";
    std::cout << "---------------------------\n\n";
    for (int i = 0; i < 10; ++i) {
        Point2D* t_point = new Point2D(arr1[i], arr2[i]);
                obstacle_set.insert(*t_point);
                delete t_point;
    }
    for (auto x : obstacle_set)
        std::cout << "Point: (" << x.x << ", " << x.y << ")\n";
    std::cout << "---------------------------\n";
    std::cout << "Size of obstacle_set: " << obstacle_set.size() << "\n";
    std::cout << "---------------------------\n\n";
}