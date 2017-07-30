; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/timeval.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.timeval = type { i64, i64 }
%struct.timezone = type { i32, i32 }

; Function Attrs: nounwind uwtable
define { i64, i64 } @curlx_tvnow() #0 !dbg !11 {
entry:
  %retval = alloca %struct.timeval, align 8
  %now = alloca %struct.timeval, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval* %now, metadata !32, metadata !33), !dbg !34
  %call = call i32 @gettimeofday(%struct.timeval* %now, %struct.timezone* null) #4, !dbg !35
  %0 = bitcast %struct.timeval* %retval to i8*, !dbg !36
  %1 = bitcast %struct.timeval* %now to i8*, !dbg !36
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 16, i32 8, i1 false), !dbg !36
  %2 = bitcast %struct.timeval* %retval to { i64, i64 }*, !dbg !37
  %3 = load { i64, i64 }, { i64, i64 }* %2, align 8, !dbg !37
  ret { i64, i64 } %3, !dbg !37
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i32 @gettimeofday(%struct.timeval*, %struct.timezone*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define i64 @curlx_tvdiff(i64 %newer.coerce0, i64 %newer.coerce1, i64 %older.coerce0, i64 %older.coerce1) #0 !dbg !20 {
entry:
  %newer = alloca %struct.timeval, align 8
  %older = alloca %struct.timeval, align 8
  %0 = bitcast %struct.timeval* %newer to { i64, i64 }*
  %1 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 0
  store i64 %newer.coerce0, i64* %1, align 8
  %2 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 1
  store i64 %newer.coerce1, i64* %2, align 8
  %3 = bitcast %struct.timeval* %older to { i64, i64 }*
  %4 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %3, i32 0, i32 0
  store i64 %older.coerce0, i64* %4, align 8
  %5 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %3, i32 0, i32 1
  store i64 %older.coerce1, i64* %5, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval* %newer, metadata !38, metadata !33), !dbg !39
  call void @llvm.dbg.declare(metadata %struct.timeval* %older, metadata !40, metadata !33), !dbg !41
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %newer, i32 0, i32 0, !dbg !42
  %6 = load i64, i64* %tv_sec, align 8, !dbg !42
  %tv_sec1 = getelementptr inbounds %struct.timeval, %struct.timeval* %older, i32 0, i32 0, !dbg !43
  %7 = load i64, i64* %tv_sec1, align 8, !dbg !43
  %sub = sub nsw i64 %6, %7, !dbg !44
  %mul = mul nsw i64 %sub, 1000, !dbg !45
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %newer, i32 0, i32 1, !dbg !46
  %8 = load i64, i64* %tv_usec, align 8, !dbg !46
  %tv_usec2 = getelementptr inbounds %struct.timeval, %struct.timeval* %older, i32 0, i32 1, !dbg !47
  %9 = load i64, i64* %tv_usec2, align 8, !dbg !47
  %sub3 = sub nsw i64 %8, %9, !dbg !48
  %div = sdiv i64 %sub3, 1000, !dbg !49
  %add = add nsw i64 %mul, %div, !dbg !50
  ret i64 %add, !dbg !51
}

; Function Attrs: nounwind uwtable
define double @curlx_tvdiff_secs(i64 %newer.coerce0, i64 %newer.coerce1, i64 %older.coerce0, i64 %older.coerce1) #0 !dbg !23 {
entry:
  %retval = alloca double, align 8
  %newer = alloca %struct.timeval, align 8
  %older = alloca %struct.timeval, align 8
  %0 = bitcast %struct.timeval* %newer to { i64, i64 }*
  %1 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 0
  store i64 %newer.coerce0, i64* %1, align 8
  %2 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 1
  store i64 %newer.coerce1, i64* %2, align 8
  %3 = bitcast %struct.timeval* %older to { i64, i64 }*
  %4 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %3, i32 0, i32 0
  store i64 %older.coerce0, i64* %4, align 8
  %5 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %3, i32 0, i32 1
  store i64 %older.coerce1, i64* %5, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval* %newer, metadata !52, metadata !33), !dbg !53
  call void @llvm.dbg.declare(metadata %struct.timeval* %older, metadata !54, metadata !33), !dbg !55
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %newer, i32 0, i32 0, !dbg !56
  %6 = load i64, i64* %tv_sec, align 8, !dbg !56
  %tv_sec1 = getelementptr inbounds %struct.timeval, %struct.timeval* %older, i32 0, i32 0, !dbg !58
  %7 = load i64, i64* %tv_sec1, align 8, !dbg !58
  %cmp = icmp ne i64 %6, %7, !dbg !59
  br i1 %cmp, label %if.then, label %if.end, !dbg !60

if.then:                                          ; preds = %entry
  %tv_sec2 = getelementptr inbounds %struct.timeval, %struct.timeval* %newer, i32 0, i32 0, !dbg !61
  %8 = load i64, i64* %tv_sec2, align 8, !dbg !61
  %tv_sec3 = getelementptr inbounds %struct.timeval, %struct.timeval* %older, i32 0, i32 0, !dbg !62
  %9 = load i64, i64* %tv_sec3, align 8, !dbg !62
  %sub = sub nsw i64 %8, %9, !dbg !63
  %conv = sitofp i64 %sub to double, !dbg !64
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %newer, i32 0, i32 1, !dbg !65
  %10 = load i64, i64* %tv_usec, align 8, !dbg !65
  %tv_usec4 = getelementptr inbounds %struct.timeval, %struct.timeval* %older, i32 0, i32 1, !dbg !66
  %11 = load i64, i64* %tv_usec4, align 8, !dbg !66
  %sub5 = sub nsw i64 %10, %11, !dbg !67
  %conv6 = sitofp i64 %sub5 to double, !dbg !68
  %div = fdiv double %conv6, 1.000000e+06, !dbg !69
  %add = fadd double %conv, %div, !dbg !70
  store double %add, double* %retval, align 8, !dbg !71
  br label %return, !dbg !71

if.end:                                           ; preds = %entry
  %tv_usec7 = getelementptr inbounds %struct.timeval, %struct.timeval* %newer, i32 0, i32 1, !dbg !72
  %12 = load i64, i64* %tv_usec7, align 8, !dbg !72
  %tv_usec8 = getelementptr inbounds %struct.timeval, %struct.timeval* %older, i32 0, i32 1, !dbg !73
  %13 = load i64, i64* %tv_usec8, align 8, !dbg !73
  %sub9 = sub nsw i64 %12, %13, !dbg !74
  %conv10 = sitofp i64 %sub9 to double, !dbg !75
  %div11 = fdiv double %conv10, 1.000000e+06, !dbg !76
  store double %div11, double* %retval, align 8, !dbg !77
  br label %return, !dbg !77

return:                                           ; preds = %if.end, %if.then
  %14 = load double, double* %retval, align 8, !dbg !78
  ret double %14, !dbg !78
}

; Function Attrs: nounwind uwtable
define i64 @Curl_tvlong(i64 %t1.coerce0, i64 %t1.coerce1) #0 !dbg !26 {
entry:
  %t1 = alloca %struct.timeval, align 8
  %0 = bitcast %struct.timeval* %t1 to { i64, i64 }*
  %1 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 0
  store i64 %t1.coerce0, i64* %1, align 8
  %2 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 1
  store i64 %t1.coerce1, i64* %2, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval* %t1, metadata !79, metadata !33), !dbg !80
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %t1, i32 0, i32 0, !dbg !81
  %3 = load i64, i64* %tv_sec, align 8, !dbg !81
  ret i64 %3, !dbg !82
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!29, !30}
!llvm.ident = !{!31}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !10)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/timeval.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !9}
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !5, line: 75, baseType: !6)
!5 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!6 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !7, line: 139, baseType: !8)
!7 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!8 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!9 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!10 = !{!11, !20, !23, !26}
!11 = distinct !DISubprogram(name: "curlx_tvnow", scope: !1, file: !1, line: 85, type: !12, isLocal: false, isDefinition: true, scopeLine: 86, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!12 = !DISubroutineType(types: !13)
!13 = !{!14}
!14 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !15, line: 30, size: 128, align: 64, elements: !16)
!15 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!16 = !{!17, !18}
!17 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !14, file: !15, line: 32, baseType: !6, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !14, file: !15, line: 33, baseType: !19, size: 64, align: 64, offset: 64)
!19 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !7, line: 141, baseType: !8)
!20 = distinct !DISubprogram(name: "curlx_tvdiff", scope: !1, file: !1, line: 119, type: !21, isLocal: false, isDefinition: true, scopeLine: 120, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!21 = !DISubroutineType(types: !22)
!22 = !{!4, !14, !14}
!23 = distinct !DISubprogram(name: "curlx_tvdiff_secs", scope: !1, file: !1, line: 137, type: !24, isLocal: false, isDefinition: true, scopeLine: 138, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!24 = !DISubroutineType(types: !25)
!25 = !{!9, !14, !14}
!26 = distinct !DISubprogram(name: "Curl_tvlong", scope: !1, file: !1, line: 146, type: !27, isLocal: false, isDefinition: true, scopeLine: 147, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!27 = !DISubroutineType(types: !28)
!28 = !{!4, !14}
!29 = !{i32 2, !"Dwarf Version", i32 4}
!30 = !{i32 2, !"Debug Info Version", i32 3}
!31 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!32 = !DILocalVariable(name: "now", scope: !11, file: !1, line: 92, type: !14)
!33 = !DIExpression()
!34 = !DILocation(line: 92, column: 18, scope: !11)
!35 = !DILocation(line: 93, column: 9, scope: !11)
!36 = !DILocation(line: 94, column: 10, scope: !11)
!37 = !DILocation(line: 94, column: 3, scope: !11)
!38 = !DILocalVariable(name: "newer", arg: 1, scope: !20, file: !1, line: 119, type: !14)
!39 = !DILocation(line: 119, column: 36, scope: !20)
!40 = !DILocalVariable(name: "older", arg: 2, scope: !20, file: !1, line: 119, type: !14)
!41 = !DILocation(line: 119, column: 58, scope: !20)
!42 = !DILocation(line: 128, column: 17, scope: !20)
!43 = !DILocation(line: 128, column: 30, scope: !20)
!44 = !DILocation(line: 128, column: 23, scope: !20)
!45 = !DILocation(line: 128, column: 37, scope: !20)
!46 = !DILocation(line: 129, column: 20, scope: !20)
!47 = !DILocation(line: 129, column: 34, scope: !20)
!48 = !DILocation(line: 129, column: 27, scope: !20)
!49 = !DILocation(line: 129, column: 42, scope: !20)
!50 = !DILocation(line: 128, column: 42, scope: !20)
!51 = !DILocation(line: 128, column: 3, scope: !20)
!52 = !DILocalVariable(name: "newer", arg: 1, scope: !23, file: !1, line: 137, type: !14)
!53 = !DILocation(line: 137, column: 41, scope: !23)
!54 = !DILocalVariable(name: "older", arg: 2, scope: !23, file: !1, line: 137, type: !14)
!55 = !DILocation(line: 137, column: 63, scope: !23)
!56 = !DILocation(line: 139, column: 12, scope: !57)
!57 = distinct !DILexicalBlock(scope: !23, file: !1, line: 139, column: 6)
!58 = !DILocation(line: 139, column: 28, scope: !57)
!59 = !DILocation(line: 139, column: 19, scope: !57)
!60 = !DILocation(line: 139, column: 6, scope: !23)
!61 = !DILocation(line: 140, column: 27, scope: !57)
!62 = !DILocation(line: 140, column: 40, scope: !57)
!63 = !DILocation(line: 140, column: 33, scope: !57)
!64 = !DILocation(line: 140, column: 12, scope: !57)
!65 = !DILocation(line: 141, column: 22, scope: !57)
!66 = !DILocation(line: 141, column: 36, scope: !57)
!67 = !DILocation(line: 141, column: 29, scope: !57)
!68 = !DILocation(line: 141, column: 7, scope: !57)
!69 = !DILocation(line: 141, column: 44, scope: !57)
!70 = !DILocation(line: 140, column: 47, scope: !57)
!71 = !DILocation(line: 140, column: 5, scope: !57)
!72 = !DILocation(line: 142, column: 25, scope: !23)
!73 = !DILocation(line: 142, column: 39, scope: !23)
!74 = !DILocation(line: 142, column: 32, scope: !23)
!75 = !DILocation(line: 142, column: 10, scope: !23)
!76 = !DILocation(line: 142, column: 47, scope: !23)
!77 = !DILocation(line: 142, column: 3, scope: !23)
!78 = !DILocation(line: 143, column: 1, scope: !23)
!79 = !DILocalVariable(name: "t1", arg: 1, scope: !26, file: !1, line: 146, type: !14)
!80 = !DILocation(line: 146, column: 35, scope: !26)
!81 = !DILocation(line: 148, column: 13, scope: !26)
!82 = !DILocation(line: 148, column: 3, scope: !26)
