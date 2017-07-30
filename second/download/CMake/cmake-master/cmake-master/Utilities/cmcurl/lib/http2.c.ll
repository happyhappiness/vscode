; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http2.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.curl_pushheaders = type opaque

; Function Attrs: nounwind uwtable
define i8* @curl_pushheader_bynum(%struct.curl_pushheaders* %h, i64 %num) #0 !dbg !4 {
entry:
  %h.addr = alloca %struct.curl_pushheaders*, align 8
  %num.addr = alloca i64, align 8
  store %struct.curl_pushheaders* %h, %struct.curl_pushheaders** %h.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_pushheaders** %h.addr, metadata !23, metadata !24), !dbg !25
  store i64 %num, i64* %num.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %num.addr, metadata !26, metadata !24), !dbg !27
  %0 = load %struct.curl_pushheaders*, %struct.curl_pushheaders** %h.addr, align 8, !dbg !28
  %1 = load i64, i64* %num.addr, align 8, !dbg !29
  ret i8* null, !dbg !30
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i8* @curl_pushheader_byname(%struct.curl_pushheaders* %h, i8* %header) #0 !dbg !15 {
entry:
  %h.addr = alloca %struct.curl_pushheaders*, align 8
  %header.addr = alloca i8*, align 8
  store %struct.curl_pushheaders* %h, %struct.curl_pushheaders** %h.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_pushheaders** %h.addr, metadata !31, metadata !24), !dbg !32
  store i8* %header, i8** %header.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %header.addr, metadata !33, metadata !24), !dbg !34
  %0 = load %struct.curl_pushheaders*, %struct.curl_pushheaders** %h.addr, align 8, !dbg !35
  %1 = load i8*, i8** %header.addr, align 8, !dbg !36
  ret i8* null, !dbg !37
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!20, !21}
!llvm.ident = !{!22}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http2.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !15}
!4 = distinct !DISubprogram(name: "curl_pushheader_bynum", scope: !1, file: !1, line: 2220, type: !5, isLocal: false, isDefinition: true, scopeLine: 2221, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !9, !12}
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_pushheaders", file: !11, line: 422, flags: DIFlagFwdDecl)
!11 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/multi.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!12 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !13, line: 62, baseType: !14)
!13 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!14 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!15 = distinct !DISubprogram(name: "curl_pushheader_byname", scope: !1, file: !1, line: 2227, type: !16, isLocal: false, isDefinition: true, scopeLine: 2228, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!16 = !DISubroutineType(types: !17)
!17 = !{!7, !9, !18}
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !8)
!20 = !{i32 2, !"Dwarf Version", i32 4}
!21 = !{i32 2, !"Debug Info Version", i32 3}
!22 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!23 = !DILocalVariable(name: "h", arg: 1, scope: !4, file: !1, line: 2220, type: !9)
!24 = !DIExpression()
!25 = !DILocation(line: 2220, column: 54, scope: !4)
!26 = !DILocalVariable(name: "num", arg: 2, scope: !4, file: !1, line: 2220, type: !12)
!27 = !DILocation(line: 2220, column: 64, scope: !4)
!28 = !DILocation(line: 2222, column: 10, scope: !4)
!29 = !DILocation(line: 2223, column: 10, scope: !4)
!30 = !DILocation(line: 2224, column: 3, scope: !4)
!31 = !DILocalVariable(name: "h", arg: 1, scope: !15, file: !1, line: 2227, type: !9)
!32 = !DILocation(line: 2227, column: 55, scope: !15)
!33 = !DILocalVariable(name: "header", arg: 2, scope: !15, file: !1, line: 2227, type: !18)
!34 = !DILocation(line: 2227, column: 70, scope: !15)
!35 = !DILocation(line: 2229, column: 10, scope: !15)
!36 = !DILocation(line: 2230, column: 10, scope: !15)
!37 = !DILocation(line: 2231, column: 3, scope: !15)
