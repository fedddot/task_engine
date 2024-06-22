#ifndef	TASK_ENGINE_HPP
#define	TASK_ENGINE_HPP

#include <exception>
#include <memory>

#include "creator.hpp"
#include "data.hpp"
#include "engine.hpp"
#include "parser.hpp"
#include "serializer.hpp"
#include "task.hpp"

namespace engine {
	template <class Traw_data, class Treport>
	class TaskEngine: public Engine<Traw_data, Treport> {
	public:
		using EngineTask = Task<Data *>;

		using EngineTaskFactory = Creator<EngineTask *(const Data&)>;
		using EngineFailureReportCreator = Creator<Data *(const std::exception&)>;
		using EngineRawDataParser = Parser<Data *(const Traw_data&)>;
		using EngineReportSerializer = Serializer<Treport(const Data&)>;
		
		TaskEngine(const EngineTaskFactory& factory, const EngineFailureReportCreator& failure_report_creator, const EngineRawDataParser& raw_data_parser, const EngineReportSerializer& report_serializer);
		TaskEngine(const TaskEngine& other) = delete;
		TaskEngine& operator=(const TaskEngine& other) = delete;

		Treport run_task(const Traw_data& cfg) const override;
	private:
		std::unique_ptr<EngineTaskFactory> m_task_factory;
		std::unique_ptr<EngineFailureReportCreator> m_failure_report_creator;
		std::unique_ptr<EngineRawDataParser> m_raw_data_parser;
		std::unique_ptr<EngineReportSerializer> m_report_serializer;
	};

	template <class Traw_data, class Treport>
	TaskEngine<Traw_data, Treport>::TaskEngine(const EngineTaskFactory& factory, const EngineFailureReportCreator& failure_report_creator, const EngineRawDataParser& raw_data_parser, const EngineReportSerializer& report_serializer): m_task_factory(factory.clone()), m_failure_report_creator(failure_report_creator.clone()), m_raw_data_parser(raw_data_parser.clone()), m_report_serializer(report_serializer.clone()) {

	}

	template <class Traw_data, class Treport>
	inline Treport TaskEngine<Traw_data, Treport>::run_task(const Traw_data& cfg) const {
		try {
			std::unique_ptr<Data> parsed_cfg(m_raw_data_parser->parse(cfg));
			std::unique_ptr<EngineTask> task_ptr(m_task_factory->create(*parsed_cfg));
			std::unique_ptr<Data> report(task_ptr->execute());
			return m_report_serializer->serialize(*report);
		} catch (const std::exception& e) {
			std::unique_ptr<Data> report(m_failure_report_creator->create(e));
			return m_report_serializer->serialize(*report);
		}
	}
}

#endif // TASK_ENGINE_HPP