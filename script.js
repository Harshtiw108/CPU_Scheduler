document.getElementById("algorithm").addEventListener("change", function() {
    const algorithm = document.getElementById("algorithm").value;
    const quantumLabel = document.getElementById("quantumLabel");
    const quantumInput = document.getElementById("quantum");
    if (algorithm === "rr") {
        quantumLabel.style.display = "block";
        quantumInput.style.display = "block";
    } else {
        quantumLabel.style.display = "none";
        quantumInput.style.display = "none";
    }
});

async function simulateScheduling() {
    const algorithm = document.getElementById("algorithm").value;
    const processesText = document.getElementById("processes").value.trim();
    const processes = processesText.split("\n").map(line => {
        const [pid, burstTime, priority] = line.split(",").map(Number);
        return { pid, burstTime, priority };
    });

    const requestBody = {
        algorithm: algorithm,
        processes: processes
    };

    if (algorithm === "rr") {
        const quantum = document.getElementById("quantum").value;
        requestBody.quantum = parseInt(quantum, 10);
    }

    try {
        const response = await fetch("http://localhost:18080/schedule", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(requestBody)
        });

        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        const result = await response.json();
        displayResults(result);
    } catch (error) {
        console.error('There has been a problem with your fetch operation:', error);
    }
}

function displayResults(results) {
    const resultsDiv = document.getElementById("results");
    resultsDiv.innerHTML = "";

    if (!Array.isArray(results) || !results.length) {
        resultsDiv.innerHTML = "<p>No results to display.</p>";
        return;
    }

    const table = document.createElement("table");
    const headerRow = table.insertRow();
    const headers = ["PID", "Burst Time", "Priority", "Waiting Time", "Turnaround Time"];
    headers.forEach(headerText => {
        const headerCell = document.createElement("th");
        headerCell.textContent = headerText;
        headerRow.appendChild(headerCell);
    });

    results.forEach(process => {
        const row = table.insertRow();
        Object.values(process).forEach(text => {
            const cell = row.insertCell();
            cell.textContent = text;
        });
    });

    resultsDiv.appendChild(table);
}

document.getElementById("schedulingForm").addEventListener("submit", function(event) {
    event.preventDefault();
    simulateScheduling();
});
