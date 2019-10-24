#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW = 0,          // новая
	IN_PROGRESS = 1,  // в разработке
	TESTING = 2,      // на тестировании
	DONE = 3          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return persons.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		persons[person][TaskStatus::NEW] += 1;
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const string& person, int task_count) {
		TasksInfo Updated;
		TasksInfo Untouched = persons[person];
		if (Untouched[TaskStatus::NEW] <= task_count) {
			task_count -= Untouched[TaskStatus::NEW];
			Updated[TaskStatus::IN_PROGRESS] += Untouched[TaskStatus::NEW];
			Untouched.erase(TaskStatus::NEW);
		}
		else {
			Untouched[TaskStatus::NEW] -= task_count;
			Updated[TaskStatus::NEW] += task_count;
			task_count -= Updated[TaskStatus::NEW];
		}
		
		if (Untouched[TaskStatus::IN_PROGRESS] <= task_count) {
			task_count -= Untouched[TaskStatus::IN_PROGRESS];
			Updated[TaskStatus::TESTING] += Untouched[TaskStatus::IN_PROGRESS];
			Untouched.erase(TaskStatus::IN_PROGRESS);
		}
		else {
			
			Untouched[TaskStatus::IN_PROGRESS] -= task_count;
			Updated[TaskStatus::IN_PROGRESS] += task_count;
			task_count -= Updated[TaskStatus::IN_PROGRESS];
		}
		
		if (Untouched[TaskStatus::TESTING] <= task_count) {
			task_count -= Untouched[TaskStatus::TESTING];
			Updated[TaskStatus::DONE] += Untouched[TaskStatus::TESTING];
			Untouched.erase(TaskStatus::TESTING);
		}
		else {
			Untouched[TaskStatus::TESTING] -= task_count;
			Updated[TaskStatus::TESTING] += task_count;
			task_count -= Updated[TaskStatus::TESTING];
			Untouched[TaskStatus::DONE] -= task_count;
			Updated[TaskStatus::TESTING] += task_count;
			task_count -= Updated[TaskStatus::DONE];
		}
		return tie(Updated, Untouched);
	}
private:
	map<string, TasksInfo> persons;
};

int main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	return 0;
}
