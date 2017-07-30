; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmzlib/adler32.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i64 @cm_zlib_adler32(i64 %adler, i8* %buf, i32 %len) #0 !dbg !6 {
entry:
  %retval = alloca i64, align 8
  %adler.addr = alloca i64, align 8
  %buf.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %sum2 = alloca i64, align 8
  %n = alloca i32, align 4
  store i64 %adler, i64* %adler.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %adler.addr, metadata !25, metadata !26), !dbg !27
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !28, metadata !26), !dbg !29
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !30, metadata !26), !dbg !31
  call void @llvm.dbg.declare(metadata i64* %sum2, metadata !32, metadata !26), !dbg !33
  call void @llvm.dbg.declare(metadata i32* %n, metadata !34, metadata !26), !dbg !35
  %0 = load i64, i64* %adler.addr, align 8, !dbg !36
  %shr = lshr i64 %0, 16, !dbg !37
  %and = and i64 %shr, 65535, !dbg !38
  store i64 %and, i64* %sum2, align 8, !dbg !39
  %1 = load i64, i64* %adler.addr, align 8, !dbg !40
  %and1 = and i64 %1, 65535, !dbg !40
  store i64 %and1, i64* %adler.addr, align 8, !dbg !40
  %2 = load i32, i32* %len.addr, align 4, !dbg !41
  %cmp = icmp eq i32 %2, 1, !dbg !43
  br i1 %cmp, label %if.then, label %if.end11, !dbg !44

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %buf.addr, align 8, !dbg !45
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 0, !dbg !45
  %4 = load i8, i8* %arrayidx, align 1, !dbg !45
  %conv = zext i8 %4 to i64, !dbg !45
  %5 = load i64, i64* %adler.addr, align 8, !dbg !47
  %add = add i64 %5, %conv, !dbg !47
  store i64 %add, i64* %adler.addr, align 8, !dbg !47
  %6 = load i64, i64* %adler.addr, align 8, !dbg !48
  %cmp2 = icmp uge i64 %6, 65521, !dbg !50
  br i1 %cmp2, label %if.then4, label %if.end, !dbg !51

if.then4:                                         ; preds = %if.then
  %7 = load i64, i64* %adler.addr, align 8, !dbg !52
  %sub = sub i64 %7, 65521, !dbg !52
  store i64 %sub, i64* %adler.addr, align 8, !dbg !52
  br label %if.end, !dbg !53

if.end:                                           ; preds = %if.then4, %if.then
  %8 = load i64, i64* %adler.addr, align 8, !dbg !54
  %9 = load i64, i64* %sum2, align 8, !dbg !55
  %add5 = add i64 %9, %8, !dbg !55
  store i64 %add5, i64* %sum2, align 8, !dbg !55
  %10 = load i64, i64* %sum2, align 8, !dbg !56
  %cmp6 = icmp uge i64 %10, 65521, !dbg !58
  br i1 %cmp6, label %if.then8, label %if.end10, !dbg !59

if.then8:                                         ; preds = %if.end
  %11 = load i64, i64* %sum2, align 8, !dbg !60
  %sub9 = sub i64 %11, 65521, !dbg !60
  store i64 %sub9, i64* %sum2, align 8, !dbg !60
  br label %if.end10, !dbg !61

if.end10:                                         ; preds = %if.then8, %if.end
  %12 = load i64, i64* %adler.addr, align 8, !dbg !62
  %13 = load i64, i64* %sum2, align 8, !dbg !63
  %shl = shl i64 %13, 16, !dbg !64
  %or = or i64 %12, %shl, !dbg !65
  store i64 %or, i64* %retval, align 8, !dbg !66
  br label %return, !dbg !66

if.end11:                                         ; preds = %entry
  %14 = load i8*, i8** %buf.addr, align 8, !dbg !67
  %cmp12 = icmp eq i8* %14, null, !dbg !69
  br i1 %cmp12, label %if.then14, label %if.end15, !dbg !70

if.then14:                                        ; preds = %if.end11
  store i64 1, i64* %retval, align 8, !dbg !71
  br label %return, !dbg !71

if.end15:                                         ; preds = %if.end11
  %15 = load i32, i32* %len.addr, align 4, !dbg !72
  %cmp16 = icmp ult i32 %15, 16, !dbg !74
  br i1 %cmp16, label %if.then18, label %if.end29, !dbg !75

if.then18:                                        ; preds = %if.end15
  br label %while.cond, !dbg !76

while.cond:                                       ; preds = %while.body, %if.then18
  %16 = load i32, i32* %len.addr, align 4, !dbg !78
  %dec = add i32 %16, -1, !dbg !78
  store i32 %dec, i32* %len.addr, align 4, !dbg !78
  %tobool = icmp ne i32 %16, 0, !dbg !80
  br i1 %tobool, label %while.body, label %while.end, !dbg !80

while.body:                                       ; preds = %while.cond
  %17 = load i8*, i8** %buf.addr, align 8, !dbg !81
  %incdec.ptr = getelementptr inbounds i8, i8* %17, i32 1, !dbg !81
  store i8* %incdec.ptr, i8** %buf.addr, align 8, !dbg !81
  %18 = load i8, i8* %17, align 1, !dbg !83
  %conv19 = zext i8 %18 to i64, !dbg !83
  %19 = load i64, i64* %adler.addr, align 8, !dbg !84
  %add20 = add i64 %19, %conv19, !dbg !84
  store i64 %add20, i64* %adler.addr, align 8, !dbg !84
  %20 = load i64, i64* %adler.addr, align 8, !dbg !85
  %21 = load i64, i64* %sum2, align 8, !dbg !86
  %add21 = add i64 %21, %20, !dbg !86
  store i64 %add21, i64* %sum2, align 8, !dbg !86
  br label %while.cond, !dbg !87

while.end:                                        ; preds = %while.cond
  %22 = load i64, i64* %adler.addr, align 8, !dbg !89
  %cmp22 = icmp uge i64 %22, 65521, !dbg !91
  br i1 %cmp22, label %if.then24, label %if.end26, !dbg !92

if.then24:                                        ; preds = %while.end
  %23 = load i64, i64* %adler.addr, align 8, !dbg !93
  %sub25 = sub i64 %23, 65521, !dbg !93
  store i64 %sub25, i64* %adler.addr, align 8, !dbg !93
  br label %if.end26, !dbg !94

if.end26:                                         ; preds = %if.then24, %while.end
  %24 = load i64, i64* %sum2, align 8, !dbg !95
  %rem = urem i64 %24, 65521, !dbg !95
  store i64 %rem, i64* %sum2, align 8, !dbg !95
  %25 = load i64, i64* %adler.addr, align 8, !dbg !96
  %26 = load i64, i64* %sum2, align 8, !dbg !97
  %shl27 = shl i64 %26, 16, !dbg !98
  %or28 = or i64 %25, %shl27, !dbg !99
  store i64 %or28, i64* %retval, align 8, !dbg !100
  br label %return, !dbg !100

if.end29:                                         ; preds = %if.end15
  br label %while.cond30, !dbg !101

while.cond30:                                     ; preds = %do.end, %if.end29
  %27 = load i32, i32* %len.addr, align 4, !dbg !102
  %cmp31 = icmp uge i32 %27, 5552, !dbg !104
  br i1 %cmp31, label %while.body33, label %while.end103, !dbg !105

while.body33:                                     ; preds = %while.cond30
  %28 = load i32, i32* %len.addr, align 4, !dbg !106
  %sub34 = sub i32 %28, 5552, !dbg !106
  store i32 %sub34, i32* %len.addr, align 4, !dbg !106
  store i32 347, i32* %n, align 4, !dbg !108
  br label %do.body, !dbg !109

do.body:                                          ; preds = %do.cond, %while.body33
  %29 = load i8*, i8** %buf.addr, align 8, !dbg !110
  %arrayidx35 = getelementptr inbounds i8, i8* %29, i64 0, !dbg !110
  %30 = load i8, i8* %arrayidx35, align 1, !dbg !110
  %conv36 = zext i8 %30 to i64, !dbg !110
  %31 = load i64, i64* %adler.addr, align 8, !dbg !110
  %add37 = add i64 %31, %conv36, !dbg !110
  store i64 %add37, i64* %adler.addr, align 8, !dbg !110
  %32 = load i64, i64* %adler.addr, align 8, !dbg !110
  %33 = load i64, i64* %sum2, align 8, !dbg !110
  %add38 = add i64 %33, %32, !dbg !110
  store i64 %add38, i64* %sum2, align 8, !dbg !110
  %34 = load i8*, i8** %buf.addr, align 8, !dbg !113
  %arrayidx39 = getelementptr inbounds i8, i8* %34, i64 1, !dbg !113
  %35 = load i8, i8* %arrayidx39, align 1, !dbg !113
  %conv40 = zext i8 %35 to i64, !dbg !113
  %36 = load i64, i64* %adler.addr, align 8, !dbg !113
  %add41 = add i64 %36, %conv40, !dbg !113
  store i64 %add41, i64* %adler.addr, align 8, !dbg !113
  %37 = load i64, i64* %adler.addr, align 8, !dbg !113
  %38 = load i64, i64* %sum2, align 8, !dbg !113
  %add42 = add i64 %38, %37, !dbg !113
  store i64 %add42, i64* %sum2, align 8, !dbg !113
  %39 = load i8*, i8** %buf.addr, align 8, !dbg !115
  %arrayidx43 = getelementptr inbounds i8, i8* %39, i64 2, !dbg !115
  %40 = load i8, i8* %arrayidx43, align 1, !dbg !115
  %conv44 = zext i8 %40 to i64, !dbg !115
  %41 = load i64, i64* %adler.addr, align 8, !dbg !115
  %add45 = add i64 %41, %conv44, !dbg !115
  store i64 %add45, i64* %adler.addr, align 8, !dbg !115
  %42 = load i64, i64* %adler.addr, align 8, !dbg !115
  %43 = load i64, i64* %sum2, align 8, !dbg !115
  %add46 = add i64 %43, %42, !dbg !115
  store i64 %add46, i64* %sum2, align 8, !dbg !115
  %44 = load i8*, i8** %buf.addr, align 8, !dbg !117
  %arrayidx47 = getelementptr inbounds i8, i8* %44, i64 3, !dbg !117
  %45 = load i8, i8* %arrayidx47, align 1, !dbg !117
  %conv48 = zext i8 %45 to i64, !dbg !117
  %46 = load i64, i64* %adler.addr, align 8, !dbg !117
  %add49 = add i64 %46, %conv48, !dbg !117
  store i64 %add49, i64* %adler.addr, align 8, !dbg !117
  %47 = load i64, i64* %adler.addr, align 8, !dbg !117
  %48 = load i64, i64* %sum2, align 8, !dbg !117
  %add50 = add i64 %48, %47, !dbg !117
  store i64 %add50, i64* %sum2, align 8, !dbg !117
  %49 = load i8*, i8** %buf.addr, align 8, !dbg !119
  %arrayidx51 = getelementptr inbounds i8, i8* %49, i64 4, !dbg !119
  %50 = load i8, i8* %arrayidx51, align 1, !dbg !119
  %conv52 = zext i8 %50 to i64, !dbg !119
  %51 = load i64, i64* %adler.addr, align 8, !dbg !119
  %add53 = add i64 %51, %conv52, !dbg !119
  store i64 %add53, i64* %adler.addr, align 8, !dbg !119
  %52 = load i64, i64* %adler.addr, align 8, !dbg !119
  %53 = load i64, i64* %sum2, align 8, !dbg !119
  %add54 = add i64 %53, %52, !dbg !119
  store i64 %add54, i64* %sum2, align 8, !dbg !119
  %54 = load i8*, i8** %buf.addr, align 8, !dbg !121
  %arrayidx55 = getelementptr inbounds i8, i8* %54, i64 5, !dbg !121
  %55 = load i8, i8* %arrayidx55, align 1, !dbg !121
  %conv56 = zext i8 %55 to i64, !dbg !121
  %56 = load i64, i64* %adler.addr, align 8, !dbg !121
  %add57 = add i64 %56, %conv56, !dbg !121
  store i64 %add57, i64* %adler.addr, align 8, !dbg !121
  %57 = load i64, i64* %adler.addr, align 8, !dbg !121
  %58 = load i64, i64* %sum2, align 8, !dbg !121
  %add58 = add i64 %58, %57, !dbg !121
  store i64 %add58, i64* %sum2, align 8, !dbg !121
  %59 = load i8*, i8** %buf.addr, align 8, !dbg !123
  %arrayidx59 = getelementptr inbounds i8, i8* %59, i64 6, !dbg !123
  %60 = load i8, i8* %arrayidx59, align 1, !dbg !123
  %conv60 = zext i8 %60 to i64, !dbg !123
  %61 = load i64, i64* %adler.addr, align 8, !dbg !123
  %add61 = add i64 %61, %conv60, !dbg !123
  store i64 %add61, i64* %adler.addr, align 8, !dbg !123
  %62 = load i64, i64* %adler.addr, align 8, !dbg !123
  %63 = load i64, i64* %sum2, align 8, !dbg !123
  %add62 = add i64 %63, %62, !dbg !123
  store i64 %add62, i64* %sum2, align 8, !dbg !123
  %64 = load i8*, i8** %buf.addr, align 8, !dbg !125
  %arrayidx63 = getelementptr inbounds i8, i8* %64, i64 7, !dbg !125
  %65 = load i8, i8* %arrayidx63, align 1, !dbg !125
  %conv64 = zext i8 %65 to i64, !dbg !125
  %66 = load i64, i64* %adler.addr, align 8, !dbg !125
  %add65 = add i64 %66, %conv64, !dbg !125
  store i64 %add65, i64* %adler.addr, align 8, !dbg !125
  %67 = load i64, i64* %adler.addr, align 8, !dbg !125
  %68 = load i64, i64* %sum2, align 8, !dbg !125
  %add66 = add i64 %68, %67, !dbg !125
  store i64 %add66, i64* %sum2, align 8, !dbg !125
  %69 = load i8*, i8** %buf.addr, align 8, !dbg !127
  %arrayidx67 = getelementptr inbounds i8, i8* %69, i64 8, !dbg !127
  %70 = load i8, i8* %arrayidx67, align 1, !dbg !127
  %conv68 = zext i8 %70 to i64, !dbg !127
  %71 = load i64, i64* %adler.addr, align 8, !dbg !127
  %add69 = add i64 %71, %conv68, !dbg !127
  store i64 %add69, i64* %adler.addr, align 8, !dbg !127
  %72 = load i64, i64* %adler.addr, align 8, !dbg !127
  %73 = load i64, i64* %sum2, align 8, !dbg !127
  %add70 = add i64 %73, %72, !dbg !127
  store i64 %add70, i64* %sum2, align 8, !dbg !127
  %74 = load i8*, i8** %buf.addr, align 8, !dbg !129
  %arrayidx71 = getelementptr inbounds i8, i8* %74, i64 9, !dbg !129
  %75 = load i8, i8* %arrayidx71, align 1, !dbg !129
  %conv72 = zext i8 %75 to i64, !dbg !129
  %76 = load i64, i64* %adler.addr, align 8, !dbg !129
  %add73 = add i64 %76, %conv72, !dbg !129
  store i64 %add73, i64* %adler.addr, align 8, !dbg !129
  %77 = load i64, i64* %adler.addr, align 8, !dbg !129
  %78 = load i64, i64* %sum2, align 8, !dbg !129
  %add74 = add i64 %78, %77, !dbg !129
  store i64 %add74, i64* %sum2, align 8, !dbg !129
  %79 = load i8*, i8** %buf.addr, align 8, !dbg !131
  %arrayidx75 = getelementptr inbounds i8, i8* %79, i64 10, !dbg !131
  %80 = load i8, i8* %arrayidx75, align 1, !dbg !131
  %conv76 = zext i8 %80 to i64, !dbg !131
  %81 = load i64, i64* %adler.addr, align 8, !dbg !131
  %add77 = add i64 %81, %conv76, !dbg !131
  store i64 %add77, i64* %adler.addr, align 8, !dbg !131
  %82 = load i64, i64* %adler.addr, align 8, !dbg !131
  %83 = load i64, i64* %sum2, align 8, !dbg !131
  %add78 = add i64 %83, %82, !dbg !131
  store i64 %add78, i64* %sum2, align 8, !dbg !131
  %84 = load i8*, i8** %buf.addr, align 8, !dbg !133
  %arrayidx79 = getelementptr inbounds i8, i8* %84, i64 11, !dbg !133
  %85 = load i8, i8* %arrayidx79, align 1, !dbg !133
  %conv80 = zext i8 %85 to i64, !dbg !133
  %86 = load i64, i64* %adler.addr, align 8, !dbg !133
  %add81 = add i64 %86, %conv80, !dbg !133
  store i64 %add81, i64* %adler.addr, align 8, !dbg !133
  %87 = load i64, i64* %adler.addr, align 8, !dbg !133
  %88 = load i64, i64* %sum2, align 8, !dbg !133
  %add82 = add i64 %88, %87, !dbg !133
  store i64 %add82, i64* %sum2, align 8, !dbg !133
  %89 = load i8*, i8** %buf.addr, align 8, !dbg !135
  %arrayidx83 = getelementptr inbounds i8, i8* %89, i64 12, !dbg !135
  %90 = load i8, i8* %arrayidx83, align 1, !dbg !135
  %conv84 = zext i8 %90 to i64, !dbg !135
  %91 = load i64, i64* %adler.addr, align 8, !dbg !135
  %add85 = add i64 %91, %conv84, !dbg !135
  store i64 %add85, i64* %adler.addr, align 8, !dbg !135
  %92 = load i64, i64* %adler.addr, align 8, !dbg !135
  %93 = load i64, i64* %sum2, align 8, !dbg !135
  %add86 = add i64 %93, %92, !dbg !135
  store i64 %add86, i64* %sum2, align 8, !dbg !135
  %94 = load i8*, i8** %buf.addr, align 8, !dbg !137
  %arrayidx87 = getelementptr inbounds i8, i8* %94, i64 13, !dbg !137
  %95 = load i8, i8* %arrayidx87, align 1, !dbg !137
  %conv88 = zext i8 %95 to i64, !dbg !137
  %96 = load i64, i64* %adler.addr, align 8, !dbg !137
  %add89 = add i64 %96, %conv88, !dbg !137
  store i64 %add89, i64* %adler.addr, align 8, !dbg !137
  %97 = load i64, i64* %adler.addr, align 8, !dbg !137
  %98 = load i64, i64* %sum2, align 8, !dbg !137
  %add90 = add i64 %98, %97, !dbg !137
  store i64 %add90, i64* %sum2, align 8, !dbg !137
  %99 = load i8*, i8** %buf.addr, align 8, !dbg !139
  %arrayidx91 = getelementptr inbounds i8, i8* %99, i64 14, !dbg !139
  %100 = load i8, i8* %arrayidx91, align 1, !dbg !139
  %conv92 = zext i8 %100 to i64, !dbg !139
  %101 = load i64, i64* %adler.addr, align 8, !dbg !139
  %add93 = add i64 %101, %conv92, !dbg !139
  store i64 %add93, i64* %adler.addr, align 8, !dbg !139
  %102 = load i64, i64* %adler.addr, align 8, !dbg !139
  %103 = load i64, i64* %sum2, align 8, !dbg !139
  %add94 = add i64 %103, %102, !dbg !139
  store i64 %add94, i64* %sum2, align 8, !dbg !139
  %104 = load i8*, i8** %buf.addr, align 8, !dbg !141
  %arrayidx95 = getelementptr inbounds i8, i8* %104, i64 15, !dbg !141
  %105 = load i8, i8* %arrayidx95, align 1, !dbg !141
  %conv96 = zext i8 %105 to i64, !dbg !141
  %106 = load i64, i64* %adler.addr, align 8, !dbg !141
  %add97 = add i64 %106, %conv96, !dbg !141
  store i64 %add97, i64* %adler.addr, align 8, !dbg !141
  %107 = load i64, i64* %adler.addr, align 8, !dbg !141
  %108 = load i64, i64* %sum2, align 8, !dbg !141
  %add98 = add i64 %108, %107, !dbg !141
  store i64 %add98, i64* %sum2, align 8, !dbg !141
  %109 = load i8*, i8** %buf.addr, align 8, !dbg !143
  %add.ptr = getelementptr inbounds i8, i8* %109, i64 16, !dbg !143
  store i8* %add.ptr, i8** %buf.addr, align 8, !dbg !143
  br label %do.cond, !dbg !144

do.cond:                                          ; preds = %do.body
  %110 = load i32, i32* %n, align 4, !dbg !145
  %dec99 = add i32 %110, -1, !dbg !145
  store i32 %dec99, i32* %n, align 4, !dbg !145
  %tobool100 = icmp ne i32 %dec99, 0, !dbg !147
  br i1 %tobool100, label %do.body, label %do.end, !dbg !147

do.end:                                           ; preds = %do.cond
  %111 = load i64, i64* %adler.addr, align 8, !dbg !148
  %rem101 = urem i64 %111, 65521, !dbg !148
  store i64 %rem101, i64* %adler.addr, align 8, !dbg !148
  %112 = load i64, i64* %sum2, align 8, !dbg !149
  %rem102 = urem i64 %112, 65521, !dbg !149
  store i64 %rem102, i64* %sum2, align 8, !dbg !149
  br label %while.cond30, !dbg !150

while.end103:                                     ; preds = %while.cond30
  %113 = load i32, i32* %len.addr, align 4, !dbg !152
  %tobool104 = icmp ne i32 %113, 0, !dbg !152
  br i1 %tobool104, label %if.then105, label %if.end188, !dbg !154

if.then105:                                       ; preds = %while.end103
  br label %while.cond106, !dbg !155

while.cond106:                                    ; preds = %while.body109, %if.then105
  %114 = load i32, i32* %len.addr, align 4, !dbg !157
  %cmp107 = icmp uge i32 %114, 16, !dbg !159
  br i1 %cmp107, label %while.body109, label %while.end176, !dbg !160

while.body109:                                    ; preds = %while.cond106
  %115 = load i32, i32* %len.addr, align 4, !dbg !161
  %sub110 = sub i32 %115, 16, !dbg !161
  store i32 %sub110, i32* %len.addr, align 4, !dbg !161
  %116 = load i8*, i8** %buf.addr, align 8, !dbg !163
  %arrayidx111 = getelementptr inbounds i8, i8* %116, i64 0, !dbg !163
  %117 = load i8, i8* %arrayidx111, align 1, !dbg !163
  %conv112 = zext i8 %117 to i64, !dbg !163
  %118 = load i64, i64* %adler.addr, align 8, !dbg !163
  %add113 = add i64 %118, %conv112, !dbg !163
  store i64 %add113, i64* %adler.addr, align 8, !dbg !163
  %119 = load i64, i64* %adler.addr, align 8, !dbg !163
  %120 = load i64, i64* %sum2, align 8, !dbg !163
  %add114 = add i64 %120, %119, !dbg !163
  store i64 %add114, i64* %sum2, align 8, !dbg !163
  %121 = load i8*, i8** %buf.addr, align 8, !dbg !165
  %arrayidx115 = getelementptr inbounds i8, i8* %121, i64 1, !dbg !165
  %122 = load i8, i8* %arrayidx115, align 1, !dbg !165
  %conv116 = zext i8 %122 to i64, !dbg !165
  %123 = load i64, i64* %adler.addr, align 8, !dbg !165
  %add117 = add i64 %123, %conv116, !dbg !165
  store i64 %add117, i64* %adler.addr, align 8, !dbg !165
  %124 = load i64, i64* %adler.addr, align 8, !dbg !165
  %125 = load i64, i64* %sum2, align 8, !dbg !165
  %add118 = add i64 %125, %124, !dbg !165
  store i64 %add118, i64* %sum2, align 8, !dbg !165
  %126 = load i8*, i8** %buf.addr, align 8, !dbg !167
  %arrayidx119 = getelementptr inbounds i8, i8* %126, i64 2, !dbg !167
  %127 = load i8, i8* %arrayidx119, align 1, !dbg !167
  %conv120 = zext i8 %127 to i64, !dbg !167
  %128 = load i64, i64* %adler.addr, align 8, !dbg !167
  %add121 = add i64 %128, %conv120, !dbg !167
  store i64 %add121, i64* %adler.addr, align 8, !dbg !167
  %129 = load i64, i64* %adler.addr, align 8, !dbg !167
  %130 = load i64, i64* %sum2, align 8, !dbg !167
  %add122 = add i64 %130, %129, !dbg !167
  store i64 %add122, i64* %sum2, align 8, !dbg !167
  %131 = load i8*, i8** %buf.addr, align 8, !dbg !169
  %arrayidx123 = getelementptr inbounds i8, i8* %131, i64 3, !dbg !169
  %132 = load i8, i8* %arrayidx123, align 1, !dbg !169
  %conv124 = zext i8 %132 to i64, !dbg !169
  %133 = load i64, i64* %adler.addr, align 8, !dbg !169
  %add125 = add i64 %133, %conv124, !dbg !169
  store i64 %add125, i64* %adler.addr, align 8, !dbg !169
  %134 = load i64, i64* %adler.addr, align 8, !dbg !169
  %135 = load i64, i64* %sum2, align 8, !dbg !169
  %add126 = add i64 %135, %134, !dbg !169
  store i64 %add126, i64* %sum2, align 8, !dbg !169
  %136 = load i8*, i8** %buf.addr, align 8, !dbg !171
  %arrayidx127 = getelementptr inbounds i8, i8* %136, i64 4, !dbg !171
  %137 = load i8, i8* %arrayidx127, align 1, !dbg !171
  %conv128 = zext i8 %137 to i64, !dbg !171
  %138 = load i64, i64* %adler.addr, align 8, !dbg !171
  %add129 = add i64 %138, %conv128, !dbg !171
  store i64 %add129, i64* %adler.addr, align 8, !dbg !171
  %139 = load i64, i64* %adler.addr, align 8, !dbg !171
  %140 = load i64, i64* %sum2, align 8, !dbg !171
  %add130 = add i64 %140, %139, !dbg !171
  store i64 %add130, i64* %sum2, align 8, !dbg !171
  %141 = load i8*, i8** %buf.addr, align 8, !dbg !173
  %arrayidx131 = getelementptr inbounds i8, i8* %141, i64 5, !dbg !173
  %142 = load i8, i8* %arrayidx131, align 1, !dbg !173
  %conv132 = zext i8 %142 to i64, !dbg !173
  %143 = load i64, i64* %adler.addr, align 8, !dbg !173
  %add133 = add i64 %143, %conv132, !dbg !173
  store i64 %add133, i64* %adler.addr, align 8, !dbg !173
  %144 = load i64, i64* %adler.addr, align 8, !dbg !173
  %145 = load i64, i64* %sum2, align 8, !dbg !173
  %add134 = add i64 %145, %144, !dbg !173
  store i64 %add134, i64* %sum2, align 8, !dbg !173
  %146 = load i8*, i8** %buf.addr, align 8, !dbg !175
  %arrayidx135 = getelementptr inbounds i8, i8* %146, i64 6, !dbg !175
  %147 = load i8, i8* %arrayidx135, align 1, !dbg !175
  %conv136 = zext i8 %147 to i64, !dbg !175
  %148 = load i64, i64* %adler.addr, align 8, !dbg !175
  %add137 = add i64 %148, %conv136, !dbg !175
  store i64 %add137, i64* %adler.addr, align 8, !dbg !175
  %149 = load i64, i64* %adler.addr, align 8, !dbg !175
  %150 = load i64, i64* %sum2, align 8, !dbg !175
  %add138 = add i64 %150, %149, !dbg !175
  store i64 %add138, i64* %sum2, align 8, !dbg !175
  %151 = load i8*, i8** %buf.addr, align 8, !dbg !177
  %arrayidx139 = getelementptr inbounds i8, i8* %151, i64 7, !dbg !177
  %152 = load i8, i8* %arrayidx139, align 1, !dbg !177
  %conv140 = zext i8 %152 to i64, !dbg !177
  %153 = load i64, i64* %adler.addr, align 8, !dbg !177
  %add141 = add i64 %153, %conv140, !dbg !177
  store i64 %add141, i64* %adler.addr, align 8, !dbg !177
  %154 = load i64, i64* %adler.addr, align 8, !dbg !177
  %155 = load i64, i64* %sum2, align 8, !dbg !177
  %add142 = add i64 %155, %154, !dbg !177
  store i64 %add142, i64* %sum2, align 8, !dbg !177
  %156 = load i8*, i8** %buf.addr, align 8, !dbg !179
  %arrayidx143 = getelementptr inbounds i8, i8* %156, i64 8, !dbg !179
  %157 = load i8, i8* %arrayidx143, align 1, !dbg !179
  %conv144 = zext i8 %157 to i64, !dbg !179
  %158 = load i64, i64* %adler.addr, align 8, !dbg !179
  %add145 = add i64 %158, %conv144, !dbg !179
  store i64 %add145, i64* %adler.addr, align 8, !dbg !179
  %159 = load i64, i64* %adler.addr, align 8, !dbg !179
  %160 = load i64, i64* %sum2, align 8, !dbg !179
  %add146 = add i64 %160, %159, !dbg !179
  store i64 %add146, i64* %sum2, align 8, !dbg !179
  %161 = load i8*, i8** %buf.addr, align 8, !dbg !181
  %arrayidx147 = getelementptr inbounds i8, i8* %161, i64 9, !dbg !181
  %162 = load i8, i8* %arrayidx147, align 1, !dbg !181
  %conv148 = zext i8 %162 to i64, !dbg !181
  %163 = load i64, i64* %adler.addr, align 8, !dbg !181
  %add149 = add i64 %163, %conv148, !dbg !181
  store i64 %add149, i64* %adler.addr, align 8, !dbg !181
  %164 = load i64, i64* %adler.addr, align 8, !dbg !181
  %165 = load i64, i64* %sum2, align 8, !dbg !181
  %add150 = add i64 %165, %164, !dbg !181
  store i64 %add150, i64* %sum2, align 8, !dbg !181
  %166 = load i8*, i8** %buf.addr, align 8, !dbg !183
  %arrayidx151 = getelementptr inbounds i8, i8* %166, i64 10, !dbg !183
  %167 = load i8, i8* %arrayidx151, align 1, !dbg !183
  %conv152 = zext i8 %167 to i64, !dbg !183
  %168 = load i64, i64* %adler.addr, align 8, !dbg !183
  %add153 = add i64 %168, %conv152, !dbg !183
  store i64 %add153, i64* %adler.addr, align 8, !dbg !183
  %169 = load i64, i64* %adler.addr, align 8, !dbg !183
  %170 = load i64, i64* %sum2, align 8, !dbg !183
  %add154 = add i64 %170, %169, !dbg !183
  store i64 %add154, i64* %sum2, align 8, !dbg !183
  %171 = load i8*, i8** %buf.addr, align 8, !dbg !185
  %arrayidx155 = getelementptr inbounds i8, i8* %171, i64 11, !dbg !185
  %172 = load i8, i8* %arrayidx155, align 1, !dbg !185
  %conv156 = zext i8 %172 to i64, !dbg !185
  %173 = load i64, i64* %adler.addr, align 8, !dbg !185
  %add157 = add i64 %173, %conv156, !dbg !185
  store i64 %add157, i64* %adler.addr, align 8, !dbg !185
  %174 = load i64, i64* %adler.addr, align 8, !dbg !185
  %175 = load i64, i64* %sum2, align 8, !dbg !185
  %add158 = add i64 %175, %174, !dbg !185
  store i64 %add158, i64* %sum2, align 8, !dbg !185
  %176 = load i8*, i8** %buf.addr, align 8, !dbg !187
  %arrayidx159 = getelementptr inbounds i8, i8* %176, i64 12, !dbg !187
  %177 = load i8, i8* %arrayidx159, align 1, !dbg !187
  %conv160 = zext i8 %177 to i64, !dbg !187
  %178 = load i64, i64* %adler.addr, align 8, !dbg !187
  %add161 = add i64 %178, %conv160, !dbg !187
  store i64 %add161, i64* %adler.addr, align 8, !dbg !187
  %179 = load i64, i64* %adler.addr, align 8, !dbg !187
  %180 = load i64, i64* %sum2, align 8, !dbg !187
  %add162 = add i64 %180, %179, !dbg !187
  store i64 %add162, i64* %sum2, align 8, !dbg !187
  %181 = load i8*, i8** %buf.addr, align 8, !dbg !189
  %arrayidx163 = getelementptr inbounds i8, i8* %181, i64 13, !dbg !189
  %182 = load i8, i8* %arrayidx163, align 1, !dbg !189
  %conv164 = zext i8 %182 to i64, !dbg !189
  %183 = load i64, i64* %adler.addr, align 8, !dbg !189
  %add165 = add i64 %183, %conv164, !dbg !189
  store i64 %add165, i64* %adler.addr, align 8, !dbg !189
  %184 = load i64, i64* %adler.addr, align 8, !dbg !189
  %185 = load i64, i64* %sum2, align 8, !dbg !189
  %add166 = add i64 %185, %184, !dbg !189
  store i64 %add166, i64* %sum2, align 8, !dbg !189
  %186 = load i8*, i8** %buf.addr, align 8, !dbg !191
  %arrayidx167 = getelementptr inbounds i8, i8* %186, i64 14, !dbg !191
  %187 = load i8, i8* %arrayidx167, align 1, !dbg !191
  %conv168 = zext i8 %187 to i64, !dbg !191
  %188 = load i64, i64* %adler.addr, align 8, !dbg !191
  %add169 = add i64 %188, %conv168, !dbg !191
  store i64 %add169, i64* %adler.addr, align 8, !dbg !191
  %189 = load i64, i64* %adler.addr, align 8, !dbg !191
  %190 = load i64, i64* %sum2, align 8, !dbg !191
  %add170 = add i64 %190, %189, !dbg !191
  store i64 %add170, i64* %sum2, align 8, !dbg !191
  %191 = load i8*, i8** %buf.addr, align 8, !dbg !193
  %arrayidx171 = getelementptr inbounds i8, i8* %191, i64 15, !dbg !193
  %192 = load i8, i8* %arrayidx171, align 1, !dbg !193
  %conv172 = zext i8 %192 to i64, !dbg !193
  %193 = load i64, i64* %adler.addr, align 8, !dbg !193
  %add173 = add i64 %193, %conv172, !dbg !193
  store i64 %add173, i64* %adler.addr, align 8, !dbg !193
  %194 = load i64, i64* %adler.addr, align 8, !dbg !193
  %195 = load i64, i64* %sum2, align 8, !dbg !193
  %add174 = add i64 %195, %194, !dbg !193
  store i64 %add174, i64* %sum2, align 8, !dbg !193
  %196 = load i8*, i8** %buf.addr, align 8, !dbg !195
  %add.ptr175 = getelementptr inbounds i8, i8* %196, i64 16, !dbg !195
  store i8* %add.ptr175, i8** %buf.addr, align 8, !dbg !195
  br label %while.cond106, !dbg !196

while.end176:                                     ; preds = %while.cond106
  br label %while.cond177, !dbg !198

while.cond177:                                    ; preds = %while.body180, %while.end176
  %197 = load i32, i32* %len.addr, align 4, !dbg !199
  %dec178 = add i32 %197, -1, !dbg !199
  store i32 %dec178, i32* %len.addr, align 4, !dbg !199
  %tobool179 = icmp ne i32 %197, 0, !dbg !200
  br i1 %tobool179, label %while.body180, label %while.end185, !dbg !200

while.body180:                                    ; preds = %while.cond177
  %198 = load i8*, i8** %buf.addr, align 8, !dbg !201
  %incdec.ptr181 = getelementptr inbounds i8, i8* %198, i32 1, !dbg !201
  store i8* %incdec.ptr181, i8** %buf.addr, align 8, !dbg !201
  %199 = load i8, i8* %198, align 1, !dbg !203
  %conv182 = zext i8 %199 to i64, !dbg !203
  %200 = load i64, i64* %adler.addr, align 8, !dbg !204
  %add183 = add i64 %200, %conv182, !dbg !204
  store i64 %add183, i64* %adler.addr, align 8, !dbg !204
  %201 = load i64, i64* %adler.addr, align 8, !dbg !205
  %202 = load i64, i64* %sum2, align 8, !dbg !206
  %add184 = add i64 %202, %201, !dbg !206
  store i64 %add184, i64* %sum2, align 8, !dbg !206
  br label %while.cond177, !dbg !207

while.end185:                                     ; preds = %while.cond177
  %203 = load i64, i64* %adler.addr, align 8, !dbg !208
  %rem186 = urem i64 %203, 65521, !dbg !208
  store i64 %rem186, i64* %adler.addr, align 8, !dbg !208
  %204 = load i64, i64* %sum2, align 8, !dbg !209
  %rem187 = urem i64 %204, 65521, !dbg !209
  store i64 %rem187, i64* %sum2, align 8, !dbg !209
  br label %if.end188, !dbg !210

if.end188:                                        ; preds = %while.end185, %while.end103
  %205 = load i64, i64* %adler.addr, align 8, !dbg !211
  %206 = load i64, i64* %sum2, align 8, !dbg !212
  %shl189 = shl i64 %206, 16, !dbg !213
  %or190 = or i64 %205, %shl189, !dbg !214
  store i64 %or190, i64* %retval, align 8, !dbg !215
  br label %return, !dbg !215

return:                                           ; preds = %if.end188, %if.end26, %if.then14, %if.end10
  %207 = load i64, i64* %retval, align 8, !dbg !216
  ret i64 %207, !dbg !216
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i64 @cm_zlib_adler32_combine(i64 %adler1, i64 %adler2, i64 %len2) #0 !dbg !18 {
entry:
  %adler1.addr = alloca i64, align 8
  %adler2.addr = alloca i64, align 8
  %len2.addr = alloca i64, align 8
  %sum1 = alloca i64, align 8
  %sum2 = alloca i64, align 8
  %rem = alloca i32, align 4
  store i64 %adler1, i64* %adler1.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %adler1.addr, metadata !217, metadata !26), !dbg !218
  store i64 %adler2, i64* %adler2.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %adler2.addr, metadata !219, metadata !26), !dbg !220
  store i64 %len2, i64* %len2.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len2.addr, metadata !221, metadata !26), !dbg !222
  call void @llvm.dbg.declare(metadata i64* %sum1, metadata !223, metadata !26), !dbg !224
  call void @llvm.dbg.declare(metadata i64* %sum2, metadata !225, metadata !26), !dbg !226
  call void @llvm.dbg.declare(metadata i32* %rem, metadata !227, metadata !26), !dbg !228
  %0 = load i64, i64* %len2.addr, align 8, !dbg !229
  %rem1 = urem i64 %0, 65521, !dbg !230
  %conv = trunc i64 %rem1 to i32, !dbg !231
  store i32 %conv, i32* %rem, align 4, !dbg !232
  %1 = load i64, i64* %adler1.addr, align 8, !dbg !233
  %and = and i64 %1, 65535, !dbg !234
  store i64 %and, i64* %sum1, align 8, !dbg !235
  %2 = load i32, i32* %rem, align 4, !dbg !236
  %conv2 = zext i32 %2 to i64, !dbg !236
  %3 = load i64, i64* %sum1, align 8, !dbg !237
  %mul = mul i64 %conv2, %3, !dbg !238
  store i64 %mul, i64* %sum2, align 8, !dbg !239
  %4 = load i64, i64* %sum2, align 8, !dbg !240
  %rem3 = urem i64 %4, 65521, !dbg !240
  store i64 %rem3, i64* %sum2, align 8, !dbg !240
  %5 = load i64, i64* %adler2.addr, align 8, !dbg !241
  %and4 = and i64 %5, 65535, !dbg !242
  %add = add i64 %and4, 65521, !dbg !243
  %sub = sub i64 %add, 1, !dbg !244
  %6 = load i64, i64* %sum1, align 8, !dbg !245
  %add5 = add i64 %6, %sub, !dbg !245
  store i64 %add5, i64* %sum1, align 8, !dbg !245
  %7 = load i64, i64* %adler1.addr, align 8, !dbg !246
  %shr = lshr i64 %7, 16, !dbg !247
  %and6 = and i64 %shr, 65535, !dbg !248
  %8 = load i64, i64* %adler2.addr, align 8, !dbg !249
  %shr7 = lshr i64 %8, 16, !dbg !250
  %and8 = and i64 %shr7, 65535, !dbg !251
  %add9 = add i64 %and6, %and8, !dbg !252
  %add10 = add i64 %add9, 65521, !dbg !253
  %9 = load i32, i32* %rem, align 4, !dbg !254
  %conv11 = zext i32 %9 to i64, !dbg !254
  %sub12 = sub i64 %add10, %conv11, !dbg !255
  %10 = load i64, i64* %sum2, align 8, !dbg !256
  %add13 = add i64 %10, %sub12, !dbg !256
  store i64 %add13, i64* %sum2, align 8, !dbg !256
  %11 = load i64, i64* %sum1, align 8, !dbg !257
  %cmp = icmp ugt i64 %11, 65521, !dbg !259
  br i1 %cmp, label %if.then, label %if.end, !dbg !260

if.then:                                          ; preds = %entry
  %12 = load i64, i64* %sum1, align 8, !dbg !261
  %sub15 = sub i64 %12, 65521, !dbg !261
  store i64 %sub15, i64* %sum1, align 8, !dbg !261
  br label %if.end, !dbg !263

if.end:                                           ; preds = %if.then, %entry
  %13 = load i64, i64* %sum1, align 8, !dbg !264
  %cmp16 = icmp ugt i64 %13, 65521, !dbg !266
  br i1 %cmp16, label %if.then18, label %if.end20, !dbg !267

if.then18:                                        ; preds = %if.end
  %14 = load i64, i64* %sum1, align 8, !dbg !268
  %sub19 = sub i64 %14, 65521, !dbg !268
  store i64 %sub19, i64* %sum1, align 8, !dbg !268
  br label %if.end20, !dbg !270

if.end20:                                         ; preds = %if.then18, %if.end
  %15 = load i64, i64* %sum2, align 8, !dbg !271
  %cmp21 = icmp ugt i64 %15, 131042, !dbg !273
  br i1 %cmp21, label %if.then23, label %if.end25, !dbg !274

if.then23:                                        ; preds = %if.end20
  %16 = load i64, i64* %sum2, align 8, !dbg !275
  %sub24 = sub i64 %16, 131042, !dbg !275
  store i64 %sub24, i64* %sum2, align 8, !dbg !275
  br label %if.end25, !dbg !277

if.end25:                                         ; preds = %if.then23, %if.end20
  %17 = load i64, i64* %sum2, align 8, !dbg !278
  %cmp26 = icmp ugt i64 %17, 65521, !dbg !280
  br i1 %cmp26, label %if.then28, label %if.end30, !dbg !281

if.then28:                                        ; preds = %if.end25
  %18 = load i64, i64* %sum2, align 8, !dbg !282
  %sub29 = sub i64 %18, 65521, !dbg !282
  store i64 %sub29, i64* %sum2, align 8, !dbg !282
  br label %if.end30, !dbg !284

if.end30:                                         ; preds = %if.then28, %if.end25
  %19 = load i64, i64* %sum1, align 8, !dbg !285
  %20 = load i64, i64* %sum2, align 8, !dbg !286
  %shl = shl i64 %20, 16, !dbg !287
  %or = or i64 %19, %shl, !dbg !288
  ret i64 %or, !dbg !289
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!22, !23}
!llvm.ident = !{!24}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/adler32.c", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!2 = !{}
!3 = !{!4}
!4 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!5 = !{!6, !18}
!6 = distinct !DISubprogram(name: "cm_zlib_adler32", scope: !1, file: !1, line: 57, type: !7, isLocal: false, isDefinition: true, scopeLine: 61, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !9, !12, !17}
!9 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLong", file: !10, line: 270, baseType: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zconf.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!11 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!13 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !14)
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "Bytef", file: !10, line: 276, baseType: !15)
!15 = !DIDerivedType(tag: DW_TAG_typedef, name: "Byte", file: !10, line: 267, baseType: !16)
!16 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!17 = !DIDerivedType(tag: DW_TAG_typedef, name: "uInt", file: !10, line: 269, baseType: !4)
!18 = distinct !DISubprogram(name: "cm_zlib_adler32_combine", scope: !1, file: !1, line: 128, type: !19, isLocal: false, isDefinition: true, scopeLine: 132, isOptimized: false, variables: !2)
!19 = !DISubroutineType(types: !20)
!20 = !{!9, !9, !9, !21}
!21 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!22 = !{i32 2, !"Dwarf Version", i32 4}
!23 = !{i32 2, !"Debug Info Version", i32 3}
!24 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!25 = !DILocalVariable(name: "adler", arg: 1, scope: !6, file: !1, line: 58, type: !9)
!26 = !DIExpression()
!27 = !DILocation(line: 58, column: 11, scope: !6)
!28 = !DILocalVariable(name: "buf", arg: 2, scope: !6, file: !1, line: 59, type: !12)
!29 = !DILocation(line: 59, column: 18, scope: !6)
!30 = !DILocalVariable(name: "len", arg: 3, scope: !6, file: !1, line: 60, type: !17)
!31 = !DILocation(line: 60, column: 10, scope: !6)
!32 = !DILocalVariable(name: "sum2", scope: !6, file: !1, line: 62, type: !11)
!33 = !DILocation(line: 62, column: 19, scope: !6)
!34 = !DILocalVariable(name: "n", scope: !6, file: !1, line: 63, type: !4)
!35 = !DILocation(line: 63, column: 14, scope: !6)
!36 = !DILocation(line: 66, column: 13, scope: !6)
!37 = !DILocation(line: 66, column: 19, scope: !6)
!38 = !DILocation(line: 66, column: 26, scope: !6)
!39 = !DILocation(line: 66, column: 10, scope: !6)
!40 = !DILocation(line: 67, column: 11, scope: !6)
!41 = !DILocation(line: 70, column: 9, scope: !42)
!42 = distinct !DILexicalBlock(scope: !6, file: !1, line: 70, column: 9)
!43 = !DILocation(line: 70, column: 13, scope: !42)
!44 = !DILocation(line: 70, column: 9, scope: !6)
!45 = !DILocation(line: 71, column: 18, scope: !46)
!46 = distinct !DILexicalBlock(scope: !42, file: !1, line: 70, column: 19)
!47 = !DILocation(line: 71, column: 15, scope: !46)
!48 = !DILocation(line: 72, column: 13, scope: !49)
!49 = distinct !DILexicalBlock(scope: !46, file: !1, line: 72, column: 13)
!50 = !DILocation(line: 72, column: 19, scope: !49)
!51 = !DILocation(line: 72, column: 13, scope: !46)
!52 = !DILocation(line: 73, column: 19, scope: !49)
!53 = !DILocation(line: 73, column: 13, scope: !49)
!54 = !DILocation(line: 74, column: 17, scope: !46)
!55 = !DILocation(line: 74, column: 14, scope: !46)
!56 = !DILocation(line: 75, column: 13, scope: !57)
!57 = distinct !DILexicalBlock(scope: !46, file: !1, line: 75, column: 13)
!58 = !DILocation(line: 75, column: 18, scope: !57)
!59 = !DILocation(line: 75, column: 13, scope: !46)
!60 = !DILocation(line: 76, column: 18, scope: !57)
!61 = !DILocation(line: 76, column: 13, scope: !57)
!62 = !DILocation(line: 77, column: 16, scope: !46)
!63 = !DILocation(line: 77, column: 25, scope: !46)
!64 = !DILocation(line: 77, column: 30, scope: !46)
!65 = !DILocation(line: 77, column: 22, scope: !46)
!66 = !DILocation(line: 77, column: 9, scope: !46)
!67 = !DILocation(line: 81, column: 9, scope: !68)
!68 = distinct !DILexicalBlock(scope: !6, file: !1, line: 81, column: 9)
!69 = !DILocation(line: 81, column: 13, scope: !68)
!70 = !DILocation(line: 81, column: 9, scope: !6)
!71 = !DILocation(line: 82, column: 9, scope: !68)
!72 = !DILocation(line: 85, column: 9, scope: !73)
!73 = distinct !DILexicalBlock(scope: !6, file: !1, line: 85, column: 9)
!74 = !DILocation(line: 85, column: 13, scope: !73)
!75 = !DILocation(line: 85, column: 9, scope: !6)
!76 = !DILocation(line: 86, column: 9, scope: !77)
!77 = distinct !DILexicalBlock(scope: !73, file: !1, line: 85, column: 19)
!78 = !DILocation(line: 86, column: 19, scope: !79)
!79 = !DILexicalBlockFile(scope: !77, file: !1, discriminator: 1)
!80 = !DILocation(line: 86, column: 9, scope: !79)
!81 = !DILocation(line: 87, column: 26, scope: !82)
!82 = distinct !DILexicalBlock(scope: !77, file: !1, line: 86, column: 23)
!83 = !DILocation(line: 87, column: 22, scope: !82)
!84 = !DILocation(line: 87, column: 19, scope: !82)
!85 = !DILocation(line: 88, column: 21, scope: !82)
!86 = !DILocation(line: 88, column: 18, scope: !82)
!87 = !DILocation(line: 86, column: 9, scope: !88)
!88 = !DILexicalBlockFile(scope: !77, file: !1, discriminator: 2)
!89 = !DILocation(line: 90, column: 13, scope: !90)
!90 = distinct !DILexicalBlock(scope: !77, file: !1, line: 90, column: 13)
!91 = !DILocation(line: 90, column: 19, scope: !90)
!92 = !DILocation(line: 90, column: 13, scope: !77)
!93 = !DILocation(line: 91, column: 19, scope: !90)
!94 = !DILocation(line: 91, column: 13, scope: !90)
!95 = !DILocation(line: 92, column: 9, scope: !77)
!96 = !DILocation(line: 93, column: 16, scope: !77)
!97 = !DILocation(line: 93, column: 25, scope: !77)
!98 = !DILocation(line: 93, column: 30, scope: !77)
!99 = !DILocation(line: 93, column: 22, scope: !77)
!100 = !DILocation(line: 93, column: 9, scope: !77)
!101 = !DILocation(line: 97, column: 5, scope: !6)
!102 = !DILocation(line: 97, column: 12, scope: !103)
!103 = !DILexicalBlockFile(scope: !6, file: !1, discriminator: 1)
!104 = !DILocation(line: 97, column: 16, scope: !103)
!105 = !DILocation(line: 97, column: 5, scope: !103)
!106 = !DILocation(line: 98, column: 13, scope: !107)
!107 = distinct !DILexicalBlock(scope: !6, file: !1, line: 97, column: 25)
!108 = !DILocation(line: 99, column: 11, scope: !107)
!109 = !DILocation(line: 100, column: 9, scope: !107)
!110 = !DILocation(line: 101, column: 13, scope: !111)
!111 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!112 = distinct !DILexicalBlock(scope: !107, file: !1, line: 100, column: 12)
!113 = !DILocation(line: 101, column: 13, scope: !114)
!114 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!115 = !DILocation(line: 101, column: 13, scope: !116)
!116 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!117 = !DILocation(line: 101, column: 13, scope: !118)
!118 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!119 = !DILocation(line: 101, column: 13, scope: !120)
!120 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!121 = !DILocation(line: 101, column: 13, scope: !122)
!122 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!123 = !DILocation(line: 101, column: 13, scope: !124)
!124 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!125 = !DILocation(line: 101, column: 13, scope: !126)
!126 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!127 = !DILocation(line: 101, column: 13, scope: !128)
!128 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!129 = !DILocation(line: 101, column: 13, scope: !130)
!130 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!131 = !DILocation(line: 101, column: 13, scope: !132)
!132 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!133 = !DILocation(line: 101, column: 13, scope: !134)
!134 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!135 = !DILocation(line: 101, column: 13, scope: !136)
!136 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!137 = !DILocation(line: 101, column: 13, scope: !138)
!138 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!139 = !DILocation(line: 101, column: 13, scope: !140)
!140 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!141 = !DILocation(line: 101, column: 13, scope: !142)
!142 = distinct !DILexicalBlock(scope: !112, file: !1, line: 101, column: 13)
!143 = !DILocation(line: 102, column: 17, scope: !112)
!144 = !DILocation(line: 103, column: 9, scope: !112)
!145 = !DILocation(line: 103, column: 18, scope: !146)
!146 = !DILexicalBlockFile(scope: !107, file: !1, discriminator: 1)
!147 = !DILocation(line: 103, column: 9, scope: !146)
!148 = !DILocation(line: 104, column: 9, scope: !107)
!149 = !DILocation(line: 105, column: 9, scope: !107)
!150 = !DILocation(line: 97, column: 5, scope: !151)
!151 = !DILexicalBlockFile(scope: !6, file: !1, discriminator: 2)
!152 = !DILocation(line: 109, column: 9, scope: !153)
!153 = distinct !DILexicalBlock(scope: !6, file: !1, line: 109, column: 9)
!154 = !DILocation(line: 109, column: 9, scope: !6)
!155 = !DILocation(line: 110, column: 9, scope: !156)
!156 = distinct !DILexicalBlock(scope: !153, file: !1, line: 109, column: 14)
!157 = !DILocation(line: 110, column: 16, scope: !158)
!158 = !DILexicalBlockFile(scope: !156, file: !1, discriminator: 1)
!159 = !DILocation(line: 110, column: 20, scope: !158)
!160 = !DILocation(line: 110, column: 9, scope: !158)
!161 = !DILocation(line: 111, column: 17, scope: !162)
!162 = distinct !DILexicalBlock(scope: !156, file: !1, line: 110, column: 27)
!163 = !DILocation(line: 112, column: 13, scope: !164)
!164 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!165 = !DILocation(line: 112, column: 13, scope: !166)
!166 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!167 = !DILocation(line: 112, column: 13, scope: !168)
!168 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!169 = !DILocation(line: 112, column: 13, scope: !170)
!170 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!171 = !DILocation(line: 112, column: 13, scope: !172)
!172 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!173 = !DILocation(line: 112, column: 13, scope: !174)
!174 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!175 = !DILocation(line: 112, column: 13, scope: !176)
!176 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!177 = !DILocation(line: 112, column: 13, scope: !178)
!178 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!179 = !DILocation(line: 112, column: 13, scope: !180)
!180 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!181 = !DILocation(line: 112, column: 13, scope: !182)
!182 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!183 = !DILocation(line: 112, column: 13, scope: !184)
!184 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!185 = !DILocation(line: 112, column: 13, scope: !186)
!186 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!187 = !DILocation(line: 112, column: 13, scope: !188)
!188 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!189 = !DILocation(line: 112, column: 13, scope: !190)
!190 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!191 = !DILocation(line: 112, column: 13, scope: !192)
!192 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!193 = !DILocation(line: 112, column: 13, scope: !194)
!194 = distinct !DILexicalBlock(scope: !162, file: !1, line: 112, column: 13)
!195 = !DILocation(line: 113, column: 17, scope: !162)
!196 = !DILocation(line: 110, column: 9, scope: !197)
!197 = !DILexicalBlockFile(scope: !156, file: !1, discriminator: 2)
!198 = !DILocation(line: 115, column: 9, scope: !156)
!199 = !DILocation(line: 115, column: 19, scope: !158)
!200 = !DILocation(line: 115, column: 9, scope: !158)
!201 = !DILocation(line: 116, column: 26, scope: !202)
!202 = distinct !DILexicalBlock(scope: !156, file: !1, line: 115, column: 23)
!203 = !DILocation(line: 116, column: 22, scope: !202)
!204 = !DILocation(line: 116, column: 19, scope: !202)
!205 = !DILocation(line: 117, column: 21, scope: !202)
!206 = !DILocation(line: 117, column: 18, scope: !202)
!207 = !DILocation(line: 115, column: 9, scope: !197)
!208 = !DILocation(line: 119, column: 9, scope: !156)
!209 = !DILocation(line: 120, column: 9, scope: !156)
!210 = !DILocation(line: 121, column: 5, scope: !156)
!211 = !DILocation(line: 124, column: 12, scope: !6)
!212 = !DILocation(line: 124, column: 21, scope: !6)
!213 = !DILocation(line: 124, column: 26, scope: !6)
!214 = !DILocation(line: 124, column: 18, scope: !6)
!215 = !DILocation(line: 124, column: 5, scope: !6)
!216 = !DILocation(line: 125, column: 1, scope: !6)
!217 = !DILocalVariable(name: "adler1", arg: 1, scope: !18, file: !1, line: 129, type: !9)
!218 = !DILocation(line: 129, column: 11, scope: !18)
!219 = !DILocalVariable(name: "adler2", arg: 2, scope: !18, file: !1, line: 130, type: !9)
!220 = !DILocation(line: 130, column: 11, scope: !18)
!221 = !DILocalVariable(name: "len2", arg: 3, scope: !18, file: !1, line: 131, type: !21)
!222 = !DILocation(line: 131, column: 13, scope: !18)
!223 = !DILocalVariable(name: "sum1", scope: !18, file: !1, line: 133, type: !11)
!224 = !DILocation(line: 133, column: 19, scope: !18)
!225 = !DILocalVariable(name: "sum2", scope: !18, file: !1, line: 134, type: !11)
!226 = !DILocation(line: 134, column: 19, scope: !18)
!227 = !DILocalVariable(name: "rem", scope: !18, file: !1, line: 135, type: !4)
!228 = !DILocation(line: 135, column: 14, scope: !18)
!229 = !DILocation(line: 138, column: 22, scope: !18)
!230 = !DILocation(line: 138, column: 27, scope: !18)
!231 = !DILocation(line: 138, column: 11, scope: !18)
!232 = !DILocation(line: 138, column: 9, scope: !18)
!233 = !DILocation(line: 139, column: 12, scope: !18)
!234 = !DILocation(line: 139, column: 19, scope: !18)
!235 = !DILocation(line: 139, column: 10, scope: !18)
!236 = !DILocation(line: 140, column: 12, scope: !18)
!237 = !DILocation(line: 140, column: 18, scope: !18)
!238 = !DILocation(line: 140, column: 16, scope: !18)
!239 = !DILocation(line: 140, column: 10, scope: !18)
!240 = !DILocation(line: 141, column: 5, scope: !18)
!241 = !DILocation(line: 142, column: 14, scope: !18)
!242 = !DILocation(line: 142, column: 21, scope: !18)
!243 = !DILocation(line: 142, column: 31, scope: !18)
!244 = !DILocation(line: 142, column: 38, scope: !18)
!245 = !DILocation(line: 142, column: 10, scope: !18)
!246 = !DILocation(line: 143, column: 15, scope: !18)
!247 = !DILocation(line: 143, column: 22, scope: !18)
!248 = !DILocation(line: 143, column: 29, scope: !18)
!249 = !DILocation(line: 143, column: 43, scope: !18)
!250 = !DILocation(line: 143, column: 50, scope: !18)
!251 = !DILocation(line: 143, column: 57, scope: !18)
!252 = !DILocation(line: 143, column: 39, scope: !18)
!253 = !DILocation(line: 143, column: 67, scope: !18)
!254 = !DILocation(line: 143, column: 76, scope: !18)
!255 = !DILocation(line: 143, column: 74, scope: !18)
!256 = !DILocation(line: 143, column: 10, scope: !18)
!257 = !DILocation(line: 144, column: 9, scope: !258)
!258 = distinct !DILexicalBlock(scope: !18, file: !1, line: 144, column: 9)
!259 = !DILocation(line: 144, column: 14, scope: !258)
!260 = !DILocation(line: 144, column: 9, scope: !18)
!261 = !DILocation(line: 144, column: 27, scope: !262)
!262 = !DILexicalBlockFile(scope: !258, file: !1, discriminator: 1)
!263 = !DILocation(line: 144, column: 22, scope: !262)
!264 = !DILocation(line: 145, column: 9, scope: !265)
!265 = distinct !DILexicalBlock(scope: !18, file: !1, line: 145, column: 9)
!266 = !DILocation(line: 145, column: 14, scope: !265)
!267 = !DILocation(line: 145, column: 9, scope: !18)
!268 = !DILocation(line: 145, column: 27, scope: !269)
!269 = !DILexicalBlockFile(scope: !265, file: !1, discriminator: 1)
!270 = !DILocation(line: 145, column: 22, scope: !269)
!271 = !DILocation(line: 146, column: 9, scope: !272)
!272 = distinct !DILexicalBlock(scope: !18, file: !1, line: 146, column: 9)
!273 = !DILocation(line: 146, column: 14, scope: !272)
!274 = !DILocation(line: 146, column: 9, scope: !18)
!275 = !DILocation(line: 146, column: 34, scope: !276)
!276 = !DILexicalBlockFile(scope: !272, file: !1, discriminator: 1)
!277 = !DILocation(line: 146, column: 29, scope: !276)
!278 = !DILocation(line: 147, column: 9, scope: !279)
!279 = distinct !DILexicalBlock(scope: !18, file: !1, line: 147, column: 9)
!280 = !DILocation(line: 147, column: 14, scope: !279)
!281 = !DILocation(line: 147, column: 9, scope: !18)
!282 = !DILocation(line: 147, column: 27, scope: !283)
!283 = !DILexicalBlockFile(scope: !279, file: !1, discriminator: 1)
!284 = !DILocation(line: 147, column: 22, scope: !283)
!285 = !DILocation(line: 148, column: 12, scope: !18)
!286 = !DILocation(line: 148, column: 20, scope: !18)
!287 = !DILocation(line: 148, column: 25, scope: !18)
!288 = !DILocation(line: 148, column: 17, scope: !18)
!289 = !DILocation(line: 148, column: 5, scope: !18)
