#include "MasterInclude.hpp"
#include "FSS_Base.hpp"
#include "FSS.hpp"
#include "FSSB.hpp"
#include "FSSNW.hpp"


void JobMakespanFSS(cFSS_Base *FSS, std::string s_jobNum);
void JobMakespanFSSB(cFSS_Base *FSSB, std::string s_jobNum);
void JobMakespanFSSNW(cFSS_Base *FSSNW, std::string s_jobNum);
void printSchedule(std::vector<Job>* schedule);


int main(int argc, char** argv)
{
	std::stringstream fileName;

	if (argc < 2)
	{
		std::cout << "No parameters received" << std::endl;
		exit(EXIT_FAILURE);
	} // end if
	else
	{
#ifdef _WIN64 || _WIN32
		fileName << "test\\" << std::string(argv[1]) << ".txt";
#else
		fileName << "test/" << std::string(argv[1]) << ".txt";
#endif
	} // end else

	std::string s_file = fileName.str();

    //! Initialization of the FSS
    cFSS_Base* FSS = new cFSS(s_file);

    //! Initialization of the FSS with blocking
	cFSS_Base* FSSB = new cFSSB(s_file);

    //! Initialization of the FSS with no wait
	cFSS_Base* FSSNW = new cFSSNW(s_file);
	
    //! Calculate a schedule for flowshop
    JobMakespanFSS(FSS, argv[1]);

    //! Calculate a schedule for flowshop with blocking
	JobMakespanFSSB(FSSB, argv[1]);

    //! Calculate a schedule for flowshop with no wait
	JobMakespanFSSNW(FSSNW, argv[1]);

	delete FSS;
	delete FSSB;
	delete FSSNW;

	exit(EXIT_SUCCESS);
} // end Main

void JobMakespanFSS(cFSS_Base *FSS, std::string s_jobNum)
{
	auto schedule = FSS->schedule();

    //! Calculate the makespan of the simple schedule and display it in standard output
	std::cout << std::endl << "The makespan for test " << s_jobNum << " in flowshop is: " << FSS->Makespan(*schedule) << std::endl;
	printSchedule(schedule);    

    //! Delete the schdule.
    delete schedule;
}

void JobMakespanFSSB(cFSS_Base *FSSB, std::string s_jobNum)
{
	auto schedule = FSSB->schedule();

	//! Calculate the makespan of the simple schedule and display it in standard output
	std::cout << std::endl << "The makespan for test " << s_jobNum << " in flowshop with blocking is: " << FSSB->Makespan(*schedule) << std::endl;
	printSchedule(schedule);

	//! Delete the schdule.
	delete schedule;
}

void JobMakespanFSSNW(cFSS_Base *FSSNW, std::string s_jobNum)
{
	auto schedule = FSSNW->schedule();

	//! Calculate the makespan of the simple schedule and display it in standard output
	std::cout << std::endl << "The makespan for test " << s_jobNum << " in flowshop with no wait is: " << FSSNW->Makespan(*schedule) << std::endl;
	printSchedule(schedule);

	//! Delete the schdule.
	delete schedule;
}


void printSchedule(std::vector<Job>* schedule)
{
	std::cout << "Schedule: " << (*schedule)[0].ui_index;
	for(auto i = 1; i < schedule->size(); i++)
	{
		std::cout << ", " << ((*schedule)[i].ui_index + 1); // convert base0 -> base1
	}
	std::cout << "\n";
}



