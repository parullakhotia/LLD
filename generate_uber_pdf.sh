#!/bin/bash

echo "Generating Uber System Design PDF..."

# Create CSS for better styling
cat > uber_style.css << 'EOF'
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

.er-diagram {
    background-color: #f8f9fa;
    padding: 20px;
    border-radius: 5px;
    font-family: 'Courier New', monospace;
    white-space: pre;
    overflow-x: auto;
}
EOF

# Generate HTML first
echo "Creating HTML version..."
pandoc uber_system_design.md \
    --toc \
    --toc-depth=3 \
    --css=uber_style.css \
    --metadata title="Uber System Design - SDE1 Interview Guide" \
    --metadata author="System Design Team" \
    --metadata date="$(date +%Y-%m-%d)" \
    -o uber_system_design.html

if [ $? -eq 0 ]; then
    echo "✅ HTML generated successfully: uber_system_design.html"
    echo "📄 File size: $(ls -lh uber_system_design.html | awk '{print $5}')"
    
    # Try to generate PDF using different methods
    echo "Attempting to generate PDF..."
    
    # Method 1: Try with weasyprint
    if command -v weasyprint &> /dev/null; then
        echo "Using weasyprint..."
        weasyprint uber_system_design.html uber_system_design.pdf
        if [ $? -eq 0 ]; then
            echo "✅ PDF generated successfully with weasyprint!"
            echo "📄 File size: $(ls -lh uber_system_design.pdf | awk '{print $5}')"
        else
            echo "❌ Failed with weasyprint"
        fi
    else
        echo "weasyprint not available"
    fi
    
    # Method 2: Try with wkhtmltopdf
    if command -v wkhtmltopdf &> /dev/null; then
        echo "Using wkhtmltopdf..."
        wkhtmltopdf uber_system_design.html uber_system_design.pdf
        if [ $? -eq 0 ]; then
            echo "✅ PDF generated successfully with wkhtmltopdf!"
            echo "📄 File size: $(ls -lh uber_system_design.pdf | awk '{print $5}')"
        else
            echo "❌ Failed with wkhtmltopdf"
        fi
    else
        echo "wkhtmltopdf not available"
    fi
    
    # Method 3: Try with pandoc and LaTeX
    if command -v xelatex &> /dev/null; then
        echo "Using pandoc with LaTeX..."
        pandoc uber_system_design.md \
            --pdf-engine=xelatex \
            --toc \
            --toc-depth=3 \
            --metadata title="Uber System Design - SDE1 Interview Guide" \
            --metadata author="System Design Team" \
            --metadata date="$(date +%Y-%m-%d)" \
            -o uber_system_design.pdf
        if [ $? -eq 0 ]; then
            echo "✅ PDF generated successfully with LaTeX!"
            echo "📄 File size: $(ls -lh uber_system_design.pdf | awk '{print $5}')"
        else
            echo "❌ Failed with LaTeX"
        fi
    else
        echo "LaTeX not available"
    fi
    
    echo ""
    echo "💡 If PDF generation failed, you can:"
    echo "   1. Open uber_system_design.html in your browser"
    echo "   2. Print to PDF (Ctrl/Cmd + P → Save as PDF)"
    echo "   3. Or use online converters:"
    echo "      - https://www.ilovepdf.com/html-to-pdf"
    echo "      - https://smallpdf.com/html-to-pdf"
    echo "      - https://pdfcrowd.com/html-to-pdf/"
    
else
    echo "❌ Failed to generate HTML"
    exit 1
fi

# Clean up CSS file
rm uber_style.css

echo "�� Process complete!" 