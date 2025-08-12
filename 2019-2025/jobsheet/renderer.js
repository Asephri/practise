document.getElementById('contactForm').addEventListener('submit', async (e) => {
	e.preventDefault();

	const formData = {
	email: document.getElementById('email').value,
	telephone: document.getElementById('telephone').value,
	firstName: document.getElementById('firstName').value,
	lastName: document.getElementById('lastName').value,
	homeAddress: document.getElementById('homeAddress').value,
	amountDue: document.getElementById('amountDue').value,
	deviceModel: document.getElementById('deviceModel').value,
	problem: document.getElementById('problem').value,
	otherInfo: document.getElementById('otherInfo').value,
	liabilityAgreed: document.getElementById('liability').checked,
	};

	await window.electronAPI.saveData(formData);

	document.getElementById('contactForm').reset();
	document.getElementById('contactForm').style.display = 'none';
	document.getElementById('confirmation').style.display = 'block';
});

document.getElementById('doneBtn').addEventListener('click', () => {
	document.getElementById('confirmation').style.display = 'none';
	document.getElementById('contactForm').style.display = 'block';
});
