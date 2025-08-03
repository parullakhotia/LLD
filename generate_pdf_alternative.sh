#!/bin/bash

# Alternative PDF generation using different tools

echo "Generating PDF using alternative method..."

# Method 1: Try using pandoc with weasyprint
if command -v weasyprint &> /dev/null; then
    echo "Using weasyprint..."
    pandoc urban_company_system_design.md \
        --pdf-engine=weasyprint \
        --toc \
        --toc-depth=3 \
        --metadata title="Urban Company System Design - Complete LLD" \
        --metadata author="System Design Team" \
        --metadata date="$(date +%Y-%m-%d)" \
        -o urban_company_system_design.pdf
    exit $?
fi

# Method 2: Try using pandoc with prince
if command -v prince &> /dev/null; then
    echo "Using prince..."
    pandoc urban_company_system_design.md \
        --pdf-engine=prince \
        --toc \
        --toc-depth=3 \
        --metadata title="Urban Company System Design - Complete LLD" \
        --metadata author="System Design Team" \
        --metadata date="$(date +%Y-%m-%d)" \
        -o urban_company_system_design.pdf
    exit $?
fi

# Method 3: Try using pandoc with basic LaTeX
echo "Using basic LaTeX..."
pandoc urban_company_system_design.md \
    --pdf-engine=xelatex \
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
    echo "❌ Failed to generate PDF with LaTeX"
    
    # Method 4: Create HTML and suggest manual conversion
    echo "Creating HTML version for manual conversion..."
    pandoc urban_company_system_design.md \
        --toc \
        --toc-depth=3 \
        --metadata title="Urban Company System Design - Complete LLD" \
        --metadata author="System Design Team" \
        --metadata date="$(date +%Y-%m-%d)" \
        -o urban_company_system_design.html
    
    if [ $? -eq 0 ]; then
        echo "✅ HTML generated: urban_company_system_design.html"
        echo "💡 You can open this HTML file in a browser and print to PDF"
        echo "💡 Or use online tools like:"
        echo "   - https://www.ilovepdf.com/html-to-pdf"
        echo "   - https://smallpdf.com/html-to-pdf"
        echo "   - https://pdfcrowd.com/html-to-pdf/"
    else
        echo "❌ Failed to generate HTML"
        exit 1
    fi
fi

echo "�� Process complete!" 