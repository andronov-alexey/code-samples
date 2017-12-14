class DeviceObserver : public QObject {
	Q_OBJECT

public:
	DeviceObserver();
	virtual ~DeviceObserver() override;

	bool startObserve();
	void stopObserve();

	std::vector<DeviceInfo> getDevices() const;

signals:
	void sigDeviceArrived(const DeviceInfo & _devInfo);
	void sigDeviceRemoved(const DeviceInfo & _devInfo);
	void sigDriveArrived(const DeviceInfo & _devInfo);
	void sigDriveRemoved(const DeviceInfo & _devInfo);
	void sigDriveMediaArrived(const DeviceInfo & _devInfo);
	void sigDriveMediaRemoved(const DeviceInfo & _devInfo);

	void sigScanFinished();

private:
	void _onDeviceArrived(const DeviceInfo & _devInfo);
	void _onDeviceRemoved(const DeviceInfo & _devInfo);
	void _onDriveArrived(const DeviceInfo & _devInfo);
	void _onDriveRemoved(const DeviceInfo & _devInfo);
	void _onDriveMediaArrived(const DeviceInfo & _devInfo);
	void _onDriveMediaRemoved(const DeviceInfo & _devInfo);

private:
	class Impl;
	std::unique_ptr<Impl> m_pImpl;
};
