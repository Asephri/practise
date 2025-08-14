const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');
const fs = require('fs');
const PDFDocument = require('pdfkit');
const { createObjectCsvWriter } = require('csv-writer');

function createWindow() {
	const win = new BrowserWindow({
		width: 800,
		height: 900,
		webPreferences: {
		  preload: path.join(__dirname, 'preload.js'),
		  contextIsolation: true,
		}
	});

	win.loadFile('index.html');
}

app.whenReady().then(() => {
	createWindow();

	app.on('activate', () => {
		if (BrowserWindow.getAllWindows().length === 0) createWindow();
	});
});

app.on('window-all-closed', () => {
	if (process.platform !== 'darwin') app.quit();
});

// Handle form submission.
ipcMain.handle('save-data', async (event, formData) => {
	try {
		const outputDir = path.join(__dirname, 'output');
		if (!fs.existsSync(outputDir)) {
		  fs.mkdirSync(outputDir);
		}

		const csvPath = path.join(outputDir, 'jobdata.csv');

		const today = new Date();
		const yyyy = today.getFullYear();
		const mm = String(today.getMonth() + 1).padStart(2, '0');
		const dd = String(today.getDate()).padStart(2, '0');
		const dateStr = `${yyyy}-${mm}-${dd}`;

		const namePart = `${formData.firstName.trim()}_${formData.lastName.trim()}`.replace(/\s+/g, '_');

		// Determine next available filename index.
		function getNextFileName() {
			for (let i = 1; i <= 999; i++) {
				const prefix = i.toString().padStart(2, '0');
				const fileName = `${prefix}_${namePart}_${dateStr}.pdf`;
				const filePath = path.join(outputDir, fileName);
					if (!fs.existsSync(filePath)) {
						return filePath;
					}
				}
			throw new Error('Maximum file versions reached (999)');
		}

		const pdfPath = getNextFileName();

		// Create PDF.
		const doc = new PDFDocument();
		doc.pipe(fs.createWriteStream(pdfPath));

		doc.fontSize(20).text('Job Contact Information', { underline: true, align: 'center' });
		doc.moveDown();

		const fields = [
			['Email', formData.email],
			['Telephone', formData.telephone],
			['First Name', formData.firstName],
			['Last Name', formData.lastName],
			['Home Address', formData.homeAddress],
			['Amount Due', formData.amountDue],
			['Device Model', formData.deviceModel],
			['Problem', formData.problem],
			['Other Info', formData.otherInfo || '(None)'],
		];

		fields.forEach(([label, value]) => {
			doc.fontSize(14).text(`${label}: ${value}`);
		});

		doc.moveDown();
		if (formData.liabilityAgreed) {
			doc.fontSize(12).fillColor('gray').text(
				'The submitter agreed that Gatley Computer is not liable for any data loss or miscommunication related to this job.',
				{ align: 'left' }
			);
		}

		doc.end();

		// Prepare CSV data (only selected fields).
		const fileUrl = `file://${pdfPath.replace(/\\/g, '/')}`;
		const hyperlinkFormula = `=HYPERLINK("${fileUrl}", "Open PDF")`;

		const csvData = {
			email: formData.email,
			telephone: formData.telephone,
			firstName: formData.firstName,
			lastName: formData.lastName,
			homeAddress: formData.homeAddress,
			amountDue: formData.amountDue,
			pdfPath: hyperlinkFormula,
		};

		const csvWriter = createObjectCsvWriter({
			path: csvPath,
			header: [
				{ id: 'email', title: 'Email' },
				{ id: 'telephone', title: 'Telephone' },
				{ id: 'firstName', title: 'First Name' },
				{ id: 'lastName', title: 'Last Name' },
				{ id: 'homeAddress', title: 'Home Address' },
				{ id: 'amountDue', title: 'Amount Due' },
				{ id: 'pdfPath', title: 'PDF Path' }
			],
			append: fs.existsSync(csvPath)
		});

		await csvWriter.writeRecords([csvData]);

		return { message: 'CSV saved', csvPath, pdfPath };
	} 
	catch (error) {
		console.error('Error saving data:', error);
		throw error;
	}
});
