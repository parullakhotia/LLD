#!/bin/bash

# Check if pandoc is installed
if ! command -v pandoc &> /dev/null; then
    echo "Pandoc is not installed. Installing..."
    if [[ "$OSTYPE" == "darwin"* ]]; then
        # macOS
        brew install pandoc
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        # Linux
        sudo apt-get update
        sudo apt-get install pandoc
    else
        echo "Please install pandoc manually: https://pandoc.org/installing.html"
        exit 1
    fi
fi

# Check if wkhtmltopdf is installed (for better PDF rendering)
if ! command -v wkhtmltopdf &> /dev/null; then
    echo "wkhtmltopdf is not installed. Installing..."
    if [[ "$OSTYPE" == "darwin"* ]]; then
        # macOS
        brew install wkhtmltopdf
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        # Linux
        sudo apt-get install wkhtmltopdf
    else
        echo "Please install wkhtmltopdf manually: https://wkhtmltopdf.org/downloads.html"
    fi
fi

# Create CSS for better styling
cat > urban_company_style.css << 'EOF'
body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    line-height: 1.6;
    margin: 40px;
    color: #333;
}

h1 {
    color: #2c3e50;
    border-bottom: 3px solid #3498db;
    padding-bottom: 10px;
}

h2 {
    color: #34495e;
    border-bottom: 2px solid #ecf0f1;
    padding-bottom: 5px;
    margin-top: 30px;
}

h3 {
    color: #2c3e50;
    margin-top: 25px;
}

code {
    background-color: #f8f9fa;
    padding: 2px 4px;
    border-radius: 3px;
    font-family: 'Courier New', monospace;
}

pre {
    background-color: #f8f9fa;
    padding: 15px;
    border-radius: 5px;
    border-left: 4px solid #3498db;
    overflow-x: auto;
}

table {
    border-collapse: collapse;
    width: 100%;
    margin: 20px 0;
}

th, td {
    border: 1px solid #ddd;
    padding: 12px;
    text-align: left;
}

th {
    background-color: #3498db;
    color: white;
}

tr:nth-child(even) {
    background-color: #f2f2f2;
}

blockquote {
    border-left: 4px solid #3498db;
    margin: 0;
    padding-left: 20px;
    color: #666;
}

a {
    color: #3498db;
    text-decoration: none;
}

a:hover {
    text-decoration: underline;
}

.toc {
    background-color: #f8f9fa;
    padding: 20px;
    border-radius: 5px;
    margin-bottom: 30px;
}

.toc h2 {
    margin-top: 0;
}
EOF

# Generate PDF using pandoc
echo "Generating PDF..."

pandoc urban_company_system_design.md \
    --pdf-engine=wkhtmltopdf \
    --css=urban_company_style.css \
    --toc \
    --toc-depth=3 \
    --metadata title="Urban Company System Design - Complete LLD" \
    --metadata author="System Design Team" \
    --metadata date="$(date +%Y-%m-%d)" \
    -o urban_company_system_design.pdf

if [ $? -eq 0 ]; then
    echo "✅ PDF generated successfully: urban_company_system_design.pdf"
    echo "📄 File size: $(ls -lh urban_company_system_design.pdf | awk '{print $5}')"
else
    echo "❌ Failed to generate PDF"
    exit 1
fi

# Clean up CSS file
rm urban_company_style.css

echo "🎉 PDF generation complete!" 