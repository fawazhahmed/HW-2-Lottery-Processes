#include <iostream>
#include <vector>
#include <random>
#include <ctime>  //including the libraries

class Process {
private:
    int pid;
    int num_tickets; //initialize the following in  a private class to keep it hidden 

public:
    Process(int id, int tickets) : pid(id), num_tickets(tickets) {} //constructor 

    int getPid() const {
        return pid;     //get the pid
    } 

    int getNumTickets() const {
        return num_tickets; //get the amount of tickets
    }

    void setNumTickets(int tickets) {
        num_tickets = tickets;      //set the number of tickets
    }
};

class Scheduler {
private:
    std::vector<Process> processes;  //initialize vector
    int total_tickets;   //initialize tickets

public:
    Scheduler() : total_tickets(0) {}  //default constructor

    void addProcess(const Process& process) {
        processes.push_back(process);           //add the process to a vector, the more you add
        total_tickets += process.getNumTickets();   //add each ticket 
    }

    void allocateTickets() {
        for (auto& process : processes) { //go through each ticket process
            process.setNumTickets(static_cast<int>((static_cast<double>(process.getNumTickets()) / total_tickets) * 100)); //calculate new tickets from the amount intially
        }
    }

    int selectWinner() {
        int winning_ticket = std::rand() % 100 + 1; //pick random 1--100
        int current_ticket = 0;

        for (const auto& process : processes) { //iterate through each process again
            current_ticket += process.getNumTickets(); //increment up by the amount of initial tickets
            if (current_ticket >= winning_ticket) {
                return process.getPid();  //if current ticket >= winning ticket, that is the winner
            }
        }

        return -1; // Indicates an error, should never happen
    }
    void displaySchedulerState() const {
        std::cout << "Scheduler State:" << std::endl;
        std::cout << "Total Tickets: " << total_tickets << std::endl;
        for (const auto& process : processes) {
            std::cout << "Process " << process.getPid() << " - Tickets: " << process.getNumTickets() << std::endl;
        }
    }

    void executeProcesses() {
        std::cout << "Executing processes..." << std::endl;
  
    }
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); //uses time to ensure that different random numbers are used

    Process process1(1, 10);
    Process process2(2, 10);
    Process process3(3, 30); //initialize processor with their tickets

    Scheduler scheduler;
    scheduler.addProcess(process1);
    scheduler.addProcess(process2);
    scheduler.addProcess(process3); //add the porcesses to schedule

    scheduler.allocateTickets();    //call function

    int winner = scheduler.selectWinner();  //pick a number to select winner
    scheduler.executeProcesses();  //calls the functions

    std::cout << "Process " << winner << " wins the lottery!" << std::endl; //print this

    scheduler.displaySchedulerState();

 

    return 0;
}
