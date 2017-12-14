void TaskBase::start() {
	m_bInterrupted = false;

	emit sigTaskStarted(this);

	_init();
	_start();
}

QString TaskBase::getDescription() const {
	return _getDescription();
}

TaskBase::Type TaskBase::getType() const {
	return m_type;
}

void TaskBase::interrupt() {
	m_bInterrupted = true;
}

void TaskBase::revert() {
	_revert();
}

void TaskBase::_start() {
	Q_ASSERT(false);
}

void TaskBase::_revert() {}

void TaskBase::_init() {}

QString TaskBase::_getDescription() const {
	Q_ASSERT(false);
	return "";
}

void TaskBase::_reportError(ErrorType _type, const QString & _strDescription) {
	_revert();

	emit sigTaskError(this, _type, _strDescription);
}
