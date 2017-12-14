class DeviceInfo {

public:
	void setSerialNumber(const QString & _strSerialNumber);
	QString getSerialNumber() const;

	void setName(const QString & _strName);
	QString getName() const;

	void setRemovable(bool _bRemovable);
	bool isRemovable() const;

	QVector<QStorageInfo> & getDrives();
	const QVector<QStorageInfo> & getDrives() const;

	bool isValid() const;

	bool operator== (const DeviceInfo & _other) const;
	bool operator< (const DeviceInfo & _other) const;

	friend QDataStream & operator<< (QDataStream & _out, const DeviceInfo & _deviceInfo);
	friend QDataStream & operator>> (QDataStream & _in, DeviceInfo & _deviceInfo);

private:
	QString m_strSerialNumber;
	QString m_strName;
	bool m_bRemovable;

	QVector<QStorageInfo> m_drives;
};
